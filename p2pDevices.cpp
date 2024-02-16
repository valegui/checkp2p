#include <cuda_runtime.h>
#include <helper_cuda.h>

#if CUDART_VERSION < 5000
// CUDA-C includes
#include <cuda.h>

#endif 

int main(int argc, char **argv){
    printf("%s Starting...\n\n", argv[0]);
    int deviceCount = 0;
    std::string G="";
    cudaError_t error_id = cudaGetDeviceCount(&deviceCount);
    if (deviceCount == 0){
        printf("There are no available device(s) that support CUDA\n");
        return -1;
    }

    G = G + "0";

    if (deviceCount == 1){
        printf("Detected 1 CUDA Capable device\n");
        printf("%s\n", G.c_str());
        return 0;
    }

    printf("Detected %d CUDA Capable devices", deviceCount);

    int firstgpu = 0;
    for (int i = 1; i < deviceCount; i++){
        cudaDeviceProp prop0, propX;
        cudaGetDeviceProperties(&prop0, firstgpu);
        cudaGetDeviceProperties(&propX, i);
        int accessPeer0_x, accessPeerx_0;
        cudaDeviceCanAccessPeer(&accessPeer0_x, firstgpu, i);
        cudaDeviceCanAccessPeer(&accessPeerx_0, i, firstgpu);

        if (accessPeer0_x == 0 || accessPeerx_0 == 0){
            printf("Peer to Peer access is not available between GPU%d <-> GPU%d.\n",
            firstgpu, i);
        } else {
            printf("Peer to Peer access is available between GPU%d <-> GPU%d.\n",
            firstgpu, i);
            cudaSetDevice(firstgpu);
            cudaDeviceEnablePeerAccess(i, 0);
            cudaSetDevice(i);
            cudaDeviceEnablePeerAccess(firstgpu, 0);
            const bool has_uva = (prop0.unifiedAddressing && propX.unifiedAddressing);
            if (has_uva){
                printf("Both GPUs can support UVA, enabling...\n");
                G = G + "," + std::to_string(i);
            }
        }
    }
    printf("%s\n", G.c_str());
    return 0;
}