/*
 * D3D12RenderContext.cpp
 * 
 * This file is part of the "LLGL" project (Copyright (c) 2015 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#include "D3D12RenderContext.h"
#include "D3D12RenderSystem.h"
#include "D3D12Assert.h"
#include "DXCore.h"
#include "../CheckedCast.h"
#include <LLGL/Platform/NativeHandle.h>
#include "../../Core/Helper.h"
#include <algorithm>


namespace LLGL
{


D3D12RenderContext::D3D12RenderContext(
    D3D12RenderSystem& renderSystem,
    RenderContextDescriptor desc,
    const std::shared_ptr<Window>& window) :
        renderSystem_   ( renderSystem ),
        desc_           ( desc         )
{
    /* Setup window for the render context */
    SetWindow(window, desc_.videoMode, nullptr);
    CreateWindowSizeDependentResources();
}

void D3D12RenderContext::Present()
{
    /* Present swap-chain with vsync interval */
    auto hr = swapChain_->Present(swapChainInterval_, 0);
    DXThrowIfFailed(hr, "failed to present D3D12 swap-chain");
}

/* ----- Configuration ----- */

void D3D12RenderContext::SetGraphicsAPIDependentState(const GraphicsAPIDependentStateDescriptor& state)
{
    // dummy
}

void D3D12RenderContext::SetVideoMode(const VideoModeDescriptor& videoModeDesc)
{
    if (GetVideoMode() != videoModeDesc)
    {
        //todo

        /* Update window appearance and store new video mode in base function */
        RenderContext::SetVideoMode(videoModeDesc);
    }
}

void D3D12RenderContext::SetVsync(const VsyncDescriptor& vsyncDesc)
{
    if (desc_.vsync != vsyncDesc)
    {
        desc_.vsync = vsyncDesc;
        //SetupVsyncInterval();
    }
}

void D3D12RenderContext::SetViewports(const std::vector<Viewport>& viewports)
{
    //todo
}

void D3D12RenderContext::SetScissors(const std::vector<Scissor>& scissors)
{
    //todo
}

void D3D12RenderContext::SetClearColor(const ColorRGBAf& color)
{
    //todo
}

void D3D12RenderContext::SetClearDepth(float depth)
{
    //todo
}

void D3D12RenderContext::SetClearStencil(int stencil)
{
    //todo
}

void D3D12RenderContext::ClearBuffers(long flags)
{
    //todo
}

void D3D12RenderContext::SetDrawMode(const DrawMode drawMode)
{
    //todo
}

/* ----- Hardware Buffers ------ */

void D3D12RenderContext::BindVertexBuffer(VertexBuffer& vertexBuffer)
{
    //todo
}

void D3D12RenderContext::UnbindVertexBuffer()
{
    //todo
}

void D3D12RenderContext::BindIndexBuffer(IndexBuffer& indexBuffer)
{
    //todo
}

void D3D12RenderContext::UnbindIndexBuffer()
{
    //todo
}

void D3D12RenderContext::BindConstantBuffer(unsigned int index, ConstantBuffer& constantBuffer)
{
    //todo
}

void D3D12RenderContext::UnbindConstantBuffer(unsigned int index)
{
    //todo
}

void D3D12RenderContext::BindStorageBuffer(unsigned int index, StorageBuffer& storageBuffer)
{
    //todo
}

void D3D12RenderContext::UnbindStorageBuffer(unsigned int index)
{
    //todo
}

void* D3D12RenderContext::MapStorageBuffer(StorageBuffer& storageBuffer, const BufferCPUAccess access)
{
    return nullptr;//todo
}

void D3D12RenderContext::UnmapStorageBuffer()
{
    //todo
}

/* ----- Textures ----- */

void D3D12RenderContext::BindTexture(unsigned int layer, Texture& texture)
{
    //todo
}

void D3D12RenderContext::UnbindTexture(unsigned int layer)
{
    //todo
}

void D3D12RenderContext::GenerateMips(Texture& texture)
{
    //todo
}

/* ----- Sampler States ----- */

void D3D12RenderContext::BindSampler(unsigned int layer, Sampler& sampler)
{
    //todo
}

void D3D12RenderContext::UnbindSampler(unsigned int layer)
{
    //todo
}

/* ----- Render Targets ----- */

void D3D12RenderContext::BindRenderTarget(RenderTarget& renderTarget)
{
    //todo
}

void D3D12RenderContext::UnbindRenderTarget()
{
    //todo
}

/* ----- Pipeline States ----- */

void D3D12RenderContext::BindGraphicsPipeline(GraphicsPipeline& graphicsPipeline)
{
    auto& graphicsPipelineD3D = LLGL_CAST(D3D12GraphicsPipeline&, graphicsPipeline);
    LLGL_D3D_ASSERT(gfxCommandList_.Get())->SetPipelineState(graphicsPipelineD3D.GetPipelineState());
}

void D3D12RenderContext::BindComputePipeline(ComputePipeline& computePipeline)
{
    //todo
}

/* ----- Queries ----- */

void D3D12RenderContext::BeginQuery(Query& query)
{
    //todo
}

void D3D12RenderContext::EndQuery(Query& query)
{
    //todo
}

bool D3D12RenderContext::QueryResult(Query& query, std::uint64_t& result)
{
    return false; //todo
}

/* ----- Drawing ----- */

void D3D12RenderContext::Draw(unsigned int numVertices, unsigned int firstVertex)
{
    LLGL_D3D_ASSERT(gfxCommandList_.Get())->DrawInstanced(numVertices, 1, firstVertex, 0);
}

void D3D12RenderContext::DrawIndexed(unsigned int numVertices, unsigned int firstIndex)
{
    LLGL_D3D_ASSERT(gfxCommandList_.Get())->DrawIndexedInstanced(numVertices, 1, firstIndex, 0, 0);
}

void D3D12RenderContext::DrawIndexed(unsigned int numVertices, unsigned int firstIndex, int vertexOffset)
{
    LLGL_D3D_ASSERT(gfxCommandList_.Get())->DrawIndexedInstanced(numVertices, 1, firstIndex, vertexOffset, 0);
}

void D3D12RenderContext::DrawInstanced(unsigned int numVertices, unsigned int firstVertex, unsigned int numInstances)
{
    LLGL_D3D_ASSERT(gfxCommandList_.Get())->DrawInstanced(numVertices, numInstances, firstVertex, 0);
}

void D3D12RenderContext::DrawInstanced(unsigned int numVertices, unsigned int firstVertex, unsigned int numInstances, unsigned int instanceOffset)
{
    LLGL_D3D_ASSERT(gfxCommandList_.Get())->DrawInstanced(numVertices, numInstances, firstVertex, instanceOffset);
}

void D3D12RenderContext::DrawIndexedInstanced(unsigned int numVertices, unsigned int numInstances, unsigned int firstIndex)
{
    LLGL_D3D_ASSERT(gfxCommandList_.Get())->DrawIndexedInstanced(numVertices, numInstances, firstIndex, 0, 0);
}

void D3D12RenderContext::DrawIndexedInstanced(unsigned int numVertices, unsigned int numInstances, unsigned int firstIndex, int vertexOffset)
{
    LLGL_D3D_ASSERT(gfxCommandList_.Get())->DrawIndexedInstanced(numVertices, numInstances, firstIndex, vertexOffset, 0);
}

void D3D12RenderContext::DrawIndexedInstanced(unsigned int numVertices, unsigned int numInstances, unsigned int firstIndex, int vertexOffset, unsigned int instanceOffset)
{
    LLGL_D3D_ASSERT(gfxCommandList_.Get())->DrawIndexedInstanced(numVertices, numInstances, firstIndex, vertexOffset, instanceOffset);
}

/* ----- Compute ----- */

void D3D12RenderContext::DispatchCompute(const Gs::Vector3ui& threadGroupSize)
{
    //todo
}

/* ----- Misc ----- */

void D3D12RenderContext::SyncGPU()
{
    renderSystem_.SyncGPU(fenceValues_[currentFrame_]);
}


/*
 * ======= Private: =======
 */

void D3D12RenderContext::CreateWindowSizeDependentResources()
{
    /* Wait until all previous GPU work is complete */
    SyncGPU();

    /* Setup swap chain meta data */
    numFrames_ = static_cast<UINT>(desc_.videoMode.swapChainMode);

    /* Create swap chain for window handle */
    NativeHandle wndHandle;
    GetWindow().GetNativeHandle(&wndHandle);

    DXGI_SWAP_CHAIN_DESC1 swapChainDesc;
    InitMemory(swapChainDesc);
    {
        swapChainDesc.Width                 = static_cast<UINT>(desc_.videoMode.resolution.x);
        swapChainDesc.Height                = static_cast<UINT>(desc_.videoMode.resolution.y);
        swapChainDesc.Format                = DXGI_FORMAT_B8G8R8A8_UNORM;
        swapChainDesc.Stereo                = false;
        swapChainDesc.SampleDesc.Count      = (desc_.antiAliasing.enabled ? desc_.antiAliasing.samples : 1);
        swapChainDesc.SampleDesc.Quality    = 0;
        swapChainDesc.BufferUsage           = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapChainDesc.BufferCount           = numFrames_;
        swapChainDesc.SwapEffect            = DXGI_SWAP_EFFECT_FLIP_DISCARD;
        swapChainDesc.Flags                 = 0;
        swapChainDesc.Scaling               = DXGI_SCALING_NONE;
        swapChainDesc.AlphaMode             = DXGI_ALPHA_MODE_IGNORE;
    }
    swapChain_ = renderSystem_.CreateDXSwapChain(swapChainDesc, wndHandle.window);

    /* Create descriptor heap */
    D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc;
    InitMemory(descHeapDesc);
    {
        descHeapDesc.NumDescriptors = numFrames_;
        descHeapDesc.Type           = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
        descHeapDesc.Flags          = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    }
    descHeap_ = renderSystem_.CreateDXDescriptorHeap(descHeapDesc);
    descHeap_->SetName(L"Render Target View Descriptor Heap");

    /* Update tracked fence values */
    for (UINT i = 0; i < numFrames_; ++i)
        fenceValues_[i] = fenceValues_[currentFrame_];

    /* Create command allocators */
    for (UINT i = 0; i < numFrames_; ++i)
        commandAllocs_[i] = renderSystem_.CreateDXCommandAllocator();

    /* Create graphics command list */
    gfxCommandList_ = renderSystem_.CreateDXGfxCommandList(commandAllocs_[0].Get());

    /* Create render targets */
    //todo...


}

void D3D12RenderContext::SetupSwapChainInterval(const VsyncDescriptor& desc)
{
    swapChainInterval_ = (desc.enabled ? std::max(1u, std::min(desc.interval, 4u)) : 0);
}


} // /namespace LLGL



// ================================================================================
