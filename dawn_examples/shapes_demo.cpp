/*
 * Dawn Shapes Demo
 * Demonstrates how to use Dawn (WebGPU) to draw various 3D shapes
 * Includes: Cube, Pyramid, and basic 3D transformations
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
#include <cmath>

// Shader source code with 3D transformations
const char* shaderSource = R"(
struct VertexInput {
    @location(0) position: vec3f,
    @location(1) color: vec3f,
}

struct VertexOutput {
    @builtin(position) position: vec4f,
    @location(0) color: vec3f,
}

struct Uniforms {
    modelViewProjection: mat4x4f,
}

@group(0) @binding(0) var<uniform> uniforms: Uniforms;

@vertex
fn vs_main(input: VertexInput) -> VertexOutput {
    var output: VertexOutput;
    output.position = uniforms.modelViewProjection * vec4f(input.position, 1.0);
    output.color = input.color;
    return output;
}

@fragment
fn fs_main(input: VertexOutput) -> @location(0) vec4f {
    return vec4f(input.color, 1.0);
}
)";

struct Vertex {
    float position[3];
    float color[3];
};

// Cube vertices (8 vertices with colors)
const std::vector<Vertex> cubeVertices = {
    // Front face (red)
    {{-0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}},
    {{ 0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}},
    {{ 0.5f,  0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}},
    {{-0.5f,  0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}},
    
    // Back face (green)
    {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
    {{ 0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
    {{ 0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
    {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
};

// Cube indices (36 indices for 12 triangles)
const std::vector<uint16_t> cubeIndices = {
    // Front face
    0, 1, 2,  2, 3, 0,
    // Back face
    5, 4, 7,  7, 6, 5,
    // Left face
    4, 0, 3,  3, 7, 4,
    // Right face
    1, 5, 6,  6, 2, 1,
    // Top face
    3, 2, 6,  6, 7, 3,
    // Bottom face
    4, 5, 1,  1, 0, 4,
};

// Pyramid vertices
const std::vector<Vertex> pyramidVertices = {
    // Base (yellow)
    {{-0.5f, 0.0f,  0.5f}, {1.0f, 1.0f, 0.0f}},
    {{ 0.5f, 0.0f,  0.5f}, {1.0f, 1.0f, 0.0f}},
    {{ 0.5f, 0.0f, -0.5f}, {1.0f, 1.0f, 0.0f}},
    {{-0.5f, 0.0f, -0.5f}, {1.0f, 1.0f, 0.0f}},
    
    // Apex (blue)
    {{ 0.0f, 0.8f,  0.0f}, {0.0f, 0.0f, 1.0f}},
};

// Pyramid indices
const std::vector<uint16_t> pyramidIndices = {
    // Base
    0, 2, 1,  0, 3, 2,
    // Sides
    0, 1, 4,
    1, 2, 4,
    2, 3, 4,
    3, 0, 4,
};

class DawnShapesDemo {
public:
    DawnShapesDemo() : window(nullptr), rotation(0.0f) {}
    
    ~DawnShapesDemo() {
        cleanup();
    }
    
    bool initialize() {
        if (!initializeWindow()) return false;
        if (!initializeDawn()) return false;
        if (!createBuffers()) return false;
        if (!createPipeline()) return false;
        
        return true;
    }
    
    void run() {
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
            
            // Update rotation
            rotation += 0.01f;
            
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
    
    wgpu::Buffer cubeVertexBuffer;
    wgpu::Buffer cubeIndexBuffer;
    wgpu::Buffer pyramidVertexBuffer;
    wgpu::Buffer pyramidIndexBuffer;
    wgpu::Buffer uniformBuffer;
    wgpu::BindGroup bindGroup;
    
    float rotation;
    
    bool initializeWindow() {
        if (!glfwInit()) {
            std::cerr << "Failed to initialize GLFW" << std::endl;
            return false;
        }
        
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        window = glfwCreateWindow(800, 600, "Dawn Shapes Demo", nullptr, nullptr);
        if (!window) {
            std::cerr << "Failed to create window" << std::endl;
            glfwTerminate();
            return false;
        }
        
        return true;
    }
    
    bool initializeDawn() {
        dawnProcSetProcs(&dawn::native::GetProcs());
        
        auto instanceDesc = wgpu::InstanceDescriptor{};
        instance = wgpu::CreateInstance(&instanceDesc);
        if (!instance) {
            std::cerr << "Failed to create Dawn instance" << std::endl;
            return false;
        }
        
        // Create surface (platform-specific code similar to triangle demo)
        // ... (implementation depends on platform)
        
        // Request adapter and device
        // ... (similar to triangle demo)
        
        return true;
    }
    
    bool createBuffers() {
        // Create cube vertex buffer
        wgpu::BufferDescriptor cubeVertexBufferDesc{};
        cubeVertexBufferDesc.size = cubeVertices.size() * sizeof(Vertex);
        cubeVertexBufferDesc.usage = wgpu::BufferUsage::Vertex | wgpu::BufferUsage::CopyDst;
        cubeVertexBuffer = device.CreateBuffer(&cubeVertexBufferDesc);
        device.GetQueue().WriteBuffer(cubeVertexBuffer, 0, cubeVertices.data(), cubeVertexBufferDesc.size);
        
        // Create cube index buffer
        wgpu::BufferDescriptor cubeIndexBufferDesc{};
        cubeIndexBufferDesc.size = cubeIndices.size() * sizeof(uint16_t);
        cubeIndexBufferDesc.usage = wgpu::BufferUsage::Index | wgpu::BufferUsage::CopyDst;
        cubeIndexBuffer = device.CreateBuffer(&cubeIndexBufferDesc);
        device.GetQueue().WriteBuffer(cubeIndexBuffer, 0, cubeIndices.data(), cubeIndexBufferDesc.size);
        
        // Create pyramid vertex buffer
        wgpu::BufferDescriptor pyramidVertexBufferDesc{};
        pyramidVertexBufferDesc.size = pyramidVertices.size() * sizeof(Vertex);
        pyramidVertexBufferDesc.usage = wgpu::BufferUsage::Vertex | wgpu::BufferUsage::CopyDst;
        pyramidVertexBuffer = device.CreateBuffer(&pyramidVertexBufferDesc);
        device.GetQueue().WriteBuffer(pyramidVertexBuffer, 0, pyramidVertices.data(), pyramidVertexBufferDesc.size);
        
        // Create pyramid index buffer
        wgpu::BufferDescriptor pyramidIndexBufferDesc{};
        pyramidIndexBufferDesc.size = pyramidIndices.size() * sizeof(uint16_t);
        pyramidIndexBufferDesc.usage = wgpu::BufferUsage::Index | wgpu::BufferUsage::CopyDst;
        pyramidIndexBuffer = device.CreateBuffer(&pyramidIndexBufferDesc);
        device.GetQueue().WriteBuffer(pyramidIndexBuffer, 0, pyramidIndices.data(), pyramidIndexBufferDesc.size);
        
        // Create uniform buffer
        wgpu::BufferDescriptor uniformBufferDesc{};
        uniformBufferDesc.size = 64; // 4x4 matrix = 16 floats * 4 bytes
        uniformBufferDesc.usage = wgpu::BufferUsage::Uniform | wgpu::BufferUsage::CopyDst;
        uniformBuffer = device.CreateBuffer(&uniformBufferDesc);
        
        return true;
    }
    
    bool createPipeline() {
        // Create shader module
        wgpu::ShaderModuleWGSLDescriptor wgslDesc{};
        wgslDesc.code = shaderSource;
        
        wgpu::ShaderModuleDescriptor shaderModuleDesc{};
        shaderModuleDesc.nextInChain = &wgslDesc;
        
        wgpu::ShaderModule shaderModule = device.CreateShaderModule(&shaderModuleDesc);
        
        // Create bind group layout
        wgpu::BindGroupLayoutEntry bindGroupLayoutEntry{};
        bindGroupLayoutEntry.binding = 0;
        bindGroupLayoutEntry.visibility = wgpu::ShaderStage::Vertex;
        bindGroupLayoutEntry.buffer.type = wgpu::BufferBindingType::Uniform;
        
        wgpu::BindGroupLayoutDescriptor bindGroupLayoutDesc{};
        bindGroupLayoutDesc.entryCount = 1;
        bindGroupLayoutDesc.entries = &bindGroupLayoutEntry;
        
        wgpu::BindGroupLayout bindGroupLayout = device.CreateBindGroupLayout(&bindGroupLayoutDesc);
        
        // Create bind group
        wgpu::BindGroupEntry bindGroupEntry{};
        bindGroupEntry.binding = 0;
        bindGroupEntry.buffer = uniformBuffer;
        bindGroupEntry.size = 64;
        
        wgpu::BindGroupDescriptor bindGroupDesc{};
        bindGroupDesc.layout = bindGroupLayout;
        bindGroupDesc.entryCount = 1;
        bindGroupDesc.entries = &bindGroupEntry;
        
        bindGroup = device.CreateBindGroup(&bindGroupDesc);
        
        // Create pipeline layout
        wgpu::PipelineLayoutDescriptor pipelineLayoutDesc{};
        pipelineLayoutDesc.bindGroupLayoutCount = 1;
        pipelineLayoutDesc.bindGroupLayouts = &bindGroupLayout;
        
        wgpu::PipelineLayout pipelineLayout = device.CreatePipelineLayout(&pipelineLayoutDesc);
        
        // Vertex buffer layout
        wgpu::VertexAttribute attributes[2];
        attributes[0].format = wgpu::VertexFormat::Float32x3;
        attributes[0].offset = 0;
        attributes[0].shaderLocation = 0;
        
        attributes[1].format = wgpu::VertexFormat::Float32x3;
        attributes[1].offset = 12;
        attributes[1].shaderLocation = 1;
        
        wgpu::VertexBufferLayout vertexBufferLayout{};
        vertexBufferLayout.arrayStride = sizeof(Vertex);
        vertexBufferLayout.attributeCount = 2;
        vertexBufferLayout.attributes = attributes;
        
        // Create render pipeline
        wgpu::RenderPipelineDescriptor pipelineDesc{};
        pipelineDesc.layout = pipelineLayout;
        
        pipelineDesc.vertex.module = shaderModule;
        pipelineDesc.vertex.entryPoint = "vs_main";
        pipelineDesc.vertex.bufferCount = 1;
        pipelineDesc.vertex.buffers = &vertexBufferLayout;
        
        wgpu::FragmentState fragmentState{};
        fragmentState.module = shaderModule;
        fragmentState.entryPoint = "fs_main";
        
        wgpu::ColorTargetState colorTarget{};
        colorTarget.format = wgpu::TextureFormat::BGRA8Unorm;
        colorTarget.writeMask = wgpu::ColorWriteMask::All;
        
        fragmentState.targetCount = 1;
        fragmentState.targets = &colorTarget;
        
        pipelineDesc.fragment = &fragmentState;
        pipelineDesc.primitive.topology = wgpu::PrimitiveTopology::TriangleList;
        pipelineDesc.primitive.cullMode = wgpu::CullMode::Back;
        
        wgpu::DepthStencilState depthStencilState{};
        depthStencilState.format = wgpu::TextureFormat::Depth24Plus;
        depthStencilState.depthWriteEnabled = true;
        depthStencilState.depthCompare = wgpu::CompareFunction::Less;
        pipelineDesc.depthStencil = &depthStencilState;
        
        pipelineDesc.multisample.count = 1;
        pipelineDesc.multisample.mask = ~0u;
        
        pipeline = device.CreateRenderPipeline(&pipelineDesc);
        
        return pipeline != nullptr;
    }
    
    void updateUniforms() {
        // Create model-view-projection matrix
        // Simple rotation around Y axis
        float mvp[16] = {
            std::cos(rotation), 0.0f, std::sin(rotation), 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            -std::sin(rotation), 0.0f, std::cos(rotation), 0.0f,
            0.0f, 0.0f, -3.0f, 1.0f
        };
        
        device.GetQueue().WriteBuffer(uniformBuffer, 0, mvp, 64);
    }
    
    void render() {
        updateUniforms();
        
        wgpu::TextureView backbuffer = swapChain.GetCurrentTextureView();
        if (!backbuffer) return;
        
        wgpu::CommandEncoder encoder = device.CreateCommandEncoder();
        
        wgpu::RenderPassColorAttachment colorAttachment{};
        colorAttachment.view = backbuffer;
        colorAttachment.loadOp = wgpu::LoadOp::Clear;
        colorAttachment.storeOp = wgpu::StoreOp::Store;
        colorAttachment.clearValue = {0.1, 0.1, 0.1, 1.0};
        
        wgpu::RenderPassDescriptor renderPassDesc{};
        renderPassDesc.colorAttachmentCount = 1;
        renderPassDesc.colorAttachments = &colorAttachment;
        
        wgpu::RenderPassEncoder pass = encoder.BeginRenderPass(&renderPassDesc);
        pass.SetPipeline(pipeline);
        pass.SetBindGroup(0, bindGroup);
        
        // Draw cube
        pass.SetVertexBuffer(0, cubeVertexBuffer);
        pass.SetIndexBuffer(cubeIndexBuffer, wgpu::IndexFormat::Uint16);
        pass.DrawIndexed(cubeIndices.size(), 1, 0, 0, 0);
        
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
    std::cout << "Dawn Shapes Demo" << std::endl;
    std::cout << "================" << std::endl;
    std::cout << "This demo shows how to use Dawn (WebGPU) to render 3D shapes:" << std::endl;
    std::cout << "- Rotating cube with colored faces" << std::endl;
    std::cout << "- Demonstrates vertex buffers, index buffers, and 3D transformations" << std::endl;
    
    DawnShapesDemo demo;
    
    if (!demo.initialize()) {
        std::cerr << "Failed to initialize demo" << std::endl;
        return 1;
    }
    
    demo.run();
    
    return 0;
}
