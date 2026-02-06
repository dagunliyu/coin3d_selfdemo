/*
 * Dawn Triangle Demo
 * Demonstrates how to use Dawn (WebGPU implementation) to draw a simple triangle
 */

#include <webgpu/webgpu_cpp.h>
#include <dawn/native/DawnNative.h>
#include <dawn/dawn_proc.h>
#include <GLFW/glfw3.h>
#if defined(__linux__)
#define GLFW_EXPOSE_NATIVE_X11
#elif defined(_WIN32)
#define GLFW_EXPOSE_NATIVE_WIN32
#elif defined(__APPLE__)
#define GLFW_EXPOSE_NATIVE_COCOA
#endif
#include <GLFW/glfw3native.h>

#include <iostream>
#include <vector>

// Shader source code
const char* shaderSource = R"(
@vertex
fn vs_main(@builtin(vertex_index) vertexIndex: u32) -> @builtin(position) vec4f {
    var pos = array<vec2f, 3>(
        vec2f(0.0, 0.5),
        vec2f(-0.5, -0.5),
        vec2f(0.5, -0.5)
    );
    return vec4f(pos[vertexIndex], 0.0, 1.0);
}

@fragment
fn fs_main() -> @location(0) vec4f {
    return vec4f(1.0, 0.0, 0.0, 1.0); // Red color
}
)";

class DawnTriangleDemo {
public:
    DawnTriangleDemo() : window(nullptr) {}
    
    ~DawnTriangleDemo() {
        cleanup();
    }
    
    bool initialize() {
        // Initialize GLFW
        if (!glfwInit()) {
            std::cerr << "Failed to initialize GLFW" << std::endl;
            return false;
        }
        
        // Create window
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        window = glfwCreateWindow(800, 600, "Dawn Triangle Demo", nullptr, nullptr);
        if (!window) {
            std::cerr << "Failed to create window" << std::endl;
            glfwTerminate();
            return false;
        }
        
        // Initialize Dawn
        if (!initializeDawn()) {
            return false;
        }
        
        // Create pipeline
        if (!createRenderPipeline()) {
            return false;
        }
        
        return true;
    }
    
    void run() {
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
            render();
        }
    }

private:
    GLFWwindow* window;
    wgpu::Instance instance;
    wgpu::Adapter adapter;
    wgpu::Device device;
    wgpu::Surface surface;
    wgpu::SwapChain swapChain;
    wgpu::RenderPipeline pipeline;
    
    bool initializeDawn() {
        // Create Dawn instance
        dawnProcSetProcs(&dawn::native::GetProcs());
        
        auto instanceDesc = wgpu::InstanceDescriptor{};
        instance = wgpu::CreateInstance(&instanceDesc);
        if (!instance) {
            std::cerr << "Failed to create Dawn instance" << std::endl;
            return false;
        }
        
        // Create surface
        surface = createSurface();
        if (!surface) {
            std::cerr << "Failed to create surface" << std::endl;
            return false;
        }
        
        // Request adapter
        wgpu::RequestAdapterOptions adapterOptions{};
        adapterOptions.compatibleSurface = surface;
        
        auto onAdapterRequestEnded = [](WGPURequestAdapterStatus status,
                                        WGPUAdapter adapter,
                                        char const* message,
                                        void* userdata) {
            if (status == WGPURequestAdapterStatus_Success) {
                *static_cast<wgpu::Adapter*>(userdata) = wgpu::Adapter::Acquire(adapter);
            } else {
                std::cerr << "Failed to request adapter: " << message << std::endl;
            }
        };
        
        instance.RequestAdapter(&adapterOptions, onAdapterRequestEnded, &adapter);
        
        if (!adapter) {
            std::cerr << "Failed to get adapter" << std::endl;
            return false;
        }
        
        // Request device
        wgpu::DeviceDescriptor deviceDesc{};
        
        auto onDeviceRequestEnded = [](WGPURequestDeviceStatus status,
                                       WGPUDevice device,
                                       char const* message,
                                       void* userdata) {
            if (status == WGPURequestDeviceStatus_Success) {
                *static_cast<wgpu::Device*>(userdata) = wgpu::Device::Acquire(device);
            } else {
                std::cerr << "Failed to request device: " << message << std::endl;
            }
        };
        
        adapter.RequestDevice(&deviceDesc, onDeviceRequestEnded, &device);
        
        if (!device) {
            std::cerr << "Failed to get device" << std::endl;
            return false;
        }
        
        // Configure swap chain
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        
        wgpu::SwapChainDescriptor swapChainDesc{};
        swapChainDesc.usage = wgpu::TextureUsage::RenderAttachment;
        swapChainDesc.format = wgpu::TextureFormat::BGRA8Unorm;
        swapChainDesc.width = width;
        swapChainDesc.height = height;
        swapChainDesc.presentMode = wgpu::PresentMode::Fifo;
        
        swapChain = device.CreateSwapChain(surface, &swapChainDesc);
        
        return true;
    }
    
    wgpu::Surface createSurface() {
#if defined(__linux__)
        wgpu::SurfaceDescriptorFromXlibWindow surfaceDesc{};
        surfaceDesc.display = glfwGetX11Display();
        surfaceDesc.window = glfwGetX11Window(window);
        
        wgpu::SurfaceDescriptor descriptor{};
        descriptor.nextInChain = &surfaceDesc;
        return instance.CreateSurface(&descriptor);
#elif defined(_WIN32)
        wgpu::SurfaceDescriptorFromWindowsHWND surfaceDesc{};
        surfaceDesc.hwnd = glfwGetWin32Window(window);
        surfaceDesc.hinstance = GetModuleHandle(nullptr);
        
        wgpu::SurfaceDescriptor descriptor{};
        descriptor.nextInChain = &surfaceDesc;
        return instance.CreateSurface(&descriptor);
#elif defined(__APPLE__)
        // Note: macOS surface creation requires Objective-C code to obtain the CAMetalLayer
        // For a complete implementation, see Dawn's official samples
        // This is a placeholder that will fail at runtime on macOS
        wgpu::SurfaceDescriptorFromMetalLayer surfaceDesc{};
        // surfaceDesc.layer should be set to a valid CAMetalLayer
        // This requires calling Objective-C code from C++
        
        wgpu::SurfaceDescriptor descriptor{};
        descriptor.nextInChain = &surfaceDesc;
        return instance.CreateSurface(&descriptor);
#else
        return nullptr;
#endif
    }
    
    bool createRenderPipeline() {
        // Create shader module
        wgpu::ShaderModuleWGSLDescriptor wgslDesc{};
        wgslDesc.code = shaderSource;
        
        wgpu::ShaderModuleDescriptor shaderModuleDesc{};
        shaderModuleDesc.nextInChain = &wgslDesc;
        
        wgpu::ShaderModule shaderModule = device.CreateShaderModule(&shaderModuleDesc);
        
        // Create pipeline layout
        wgpu::PipelineLayoutDescriptor pipelineLayoutDesc{};
        wgpu::PipelineLayout pipelineLayout = device.CreatePipelineLayout(&pipelineLayoutDesc);
        
        // Create render pipeline
        wgpu::RenderPipelineDescriptor pipelineDesc{};
        pipelineDesc.layout = pipelineLayout;
        
        // Vertex state
        pipelineDesc.vertex.module = shaderModule;
        pipelineDesc.vertex.entryPoint = "vs_main";
        
        // Fragment state
        wgpu::FragmentState fragmentState{};
        fragmentState.module = shaderModule;
        fragmentState.entryPoint = "fs_main";
        
        wgpu::ColorTargetState colorTarget{};
        colorTarget.format = wgpu::TextureFormat::BGRA8Unorm;
        colorTarget.writeMask = wgpu::ColorWriteMask::All;
        
        fragmentState.targetCount = 1;
        fragmentState.targets = &colorTarget;
        
        pipelineDesc.fragment = &fragmentState;
        
        // Primitive state
        pipelineDesc.primitive.topology = wgpu::PrimitiveTopology::TriangleList;
        
        // Multisample state
        pipelineDesc.multisample.count = 1;
        pipelineDesc.multisample.mask = ~0u;
        
        pipeline = device.CreateRenderPipeline(&pipelineDesc);
        
        return pipeline != nullptr;
    }
    
    void render() {
        wgpu::TextureView backbuffer = swapChain.GetCurrentTextureView();
        if (!backbuffer) {
            std::cerr << "Failed to get current texture view" << std::endl;
            return;
        }
        
        wgpu::CommandEncoder encoder = device.CreateCommandEncoder();
        
        wgpu::RenderPassColorAttachment colorAttachment{};
        colorAttachment.view = backbuffer;
        colorAttachment.loadOp = wgpu::LoadOp::Clear;
        colorAttachment.storeOp = wgpu::StoreOp::Store;
        colorAttachment.clearValue = {0.0, 0.0, 0.0, 1.0}; // Black background
        
        wgpu::RenderPassDescriptor renderPassDesc{};
        renderPassDesc.colorAttachmentCount = 1;
        renderPassDesc.colorAttachments = &colorAttachment;
        
        wgpu::RenderPassEncoder pass = encoder.BeginRenderPass(&renderPassDesc);
        pass.SetPipeline(pipeline);
        pass.Draw(3, 1, 0, 0);  // Draw 3 vertices (triangle)
        pass.End();
        
        wgpu::CommandBuffer commands = encoder.Finish();
        device.GetQueue().Submit(1, &commands);
        
        swapChain.Present();
    }
    
    void cleanup() {
        if (window) {
            glfwDestroyWindow(window);
            glfwTerminate();
        }
    }
};

int main() {
    std::cout << "Dawn Triangle Demo" << std::endl;
    std::cout << "==================" << std::endl;
    std::cout << "This demo shows how to use Dawn (WebGPU) to render a simple red triangle." << std::endl;
    
    DawnTriangleDemo demo;
    
    if (!demo.initialize()) {
        std::cerr << "Failed to initialize demo" << std::endl;
        return 1;
    }
    
    demo.run();
    
    return 0;
}
