#ifndef _RENDERTEXTURE_HPP
#define _RENDERTEXTURE_HPP

#include <KlayGE/PreDeclare.hpp>
#include <KlayGE/RenderTarget.hpp>

#pragma comment(lib, "KlayGE_Core.lib")

namespace KlayGE
{	
	class RenderTexture : public RenderTarget
	{
	public:
		TexturePtr const & GetTexture() const
			{ return privateTex_; }
		TexturePtr& GetTexture()
			{ return privateTex_; }

	protected:
		TexturePtr privateTex_;
	};
}

#endif			// _RENDERTEXTURE_HPP