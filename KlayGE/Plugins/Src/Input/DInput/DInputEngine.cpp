// DInputEngine.cpp
// KlayGE DirectInput输入引擎类 实现文件
// Ver 2.0.0
// 版权所有(C) 龚敏敏, 2003
// Homepage: http://www.enginedev.com
//
// 2.0.0
// 初次建立 (2003.8.30)
//
// 修改记录
/////////////////////////////////////////////////////////////////////////////////

#include <KlayGE/KlayGE.hpp>
#include <KlayGE/ThrowErr.hpp>
#include <KlayGE/Util.hpp>

#include <cassert>

#include <KlayGE/DInput/DInput.hpp>

#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "ole32.lib")

namespace KlayGE
{
	// 建立设备
	/////////////////////////////////////////////////////////////////////////////////
	boost::shared_ptr<IDirectInputDevice8W> CreateDevice(REFGUID guid, InputEngine& inputEng)
	{
		DInputEngine& dinputEng(static_cast<DInputEngine&>(inputEng));

		IDirectInputDevice8W* device;
		dinputEng.DInput()->CreateDevice(guid, &device, NULL);
		return MakeCOMPtr(device);
	}

	// 构造函数
	/////////////////////////////////////////////////////////////////////////////////
	DInputEngine::DInputEngine()
	{
		// 建立 DirectInput 对象
		IDirectInput8W* di;
		DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, 
			IID_PPV_ARG(IDirectInput8W, di), NULL);
		dinput_ = MakeCOMPtr(di);
	}

	// 析构函数
	/////////////////////////////////////////////////////////////////////////////////
	DInputEngine::~DInputEngine()
	{
		devices_.clear();
	}

	// 获取DirectInput接口
	/////////////////////////////////////////////////////////////////////////////////
	const boost::shared_ptr<IDirectInput8W>& DInputEngine::DInput() const
	{
		return dinput_;
	}

	// 输入引擎名称
	/////////////////////////////////////////////////////////////////////////////////
	const std::wstring& DInputEngine::Name() const
	{
		static std::wstring name(L"DirectInput Input Engine");
		return name;
	}

	// 枚举设备
	/////////////////////////////////////////////////////////////////////////////////
	void DInputEngine::EnumDevices()
	{
		TIF(dinput_->EnumDevices(DI8DEVCLASS_ALL, EnumDevicesCB, this, DIEDFL_ALLDEVICES));
	}

	// 枚举设备的回调函数
	//////////////////////////////////////////////////////////////////////////////////
	BOOL CALLBACK DInputEngine::EnumDevicesCB(LPCDIDEVICEINSTANCEW didi, void* pvRef)
	{
		DInputEngine& inputEng(*(reinterpret_cast<DInputEngine*>(pvRef)));

		InputDevicePtr device;

		switch (GET_DIDEVICE_TYPE(didi->dwDevType))
		{
		case DI8DEVTYPE_KEYBOARD:
			device = InputDevicePtr(new DInputKeyboard(didi->guidInstance, inputEng));
			break;

		case DI8DEVTYPE_MOUSE:
			device = InputDevicePtr(new DInputMouse(didi->guidInstance, inputEng));
			break;

		case DI8DEVTYPE_JOYSTICK:
			device = InputDevicePtr(new DInputJoystick(didi->guidInstance, inputEng));
			break;
		}

		device->Unacquire();
		inputEng.devices_.push_back(device);

		return DIENUM_CONTINUE;
	}
}
