// MusicBuffer.cpp
// KlayGE 音乐缓冲区类 实现文件
// Ver 2.0.0
// 版权所有(C) 龚敏敏, 2003
// Homepage: http://www.enginedev.com
//
// 2.0.0
// 初次建立 (2003.7.7)
//
// 修改记录
/////////////////////////////////////////////////////////////////////////////////

#include <KlayGE/KlayGE.hpp>
#include <KlayGE/ThrowErr.hpp>
#include <KlayGE/AudioDataSource.hpp>

#include <cassert>

#include <KlayGE/Audio.hpp>

namespace KlayGE
{
	U32 MusicBuffer::PreSecond = 2;

	// 构造函数
	/////////////////////////////////////////////////////////////////////////////////
	MusicBuffer::MusicBuffer(AudioDataSourcePtr const & dataSource)
					: AudioBuffer(dataSource)
	{
	}

	// 析构函数
	/////////////////////////////////////////////////////////////////////////////////
	MusicBuffer::~MusicBuffer()
	{
	}

	// 是否是声音
	/////////////////////////////////////////////////////////////////////////////////
	bool MusicBuffer::IsSound() const
	{
		return false;
	}

	// 缓冲区复位以便于从头播放
	/////////////////////////////////////////////////////////////////////////////////
	void MusicBuffer::Reset()
	{
		this->Stop();

		this->DoReset();
	}

	// 播放音频流
	/////////////////////////////////////////////////////////////////////////////////
	void MusicBuffer::Play(bool loop)
	{
		if (this->IsPlaying())
		{
			this->Stop();
		}

		this->DoPlay(loop);
	}

	// 停止播放音频流
	////////////////////////////////////////////////////////////////////////////////
	void MusicBuffer::Stop()
	{
		this->DoStop();

		dataSource_->Reset();
	}
}
