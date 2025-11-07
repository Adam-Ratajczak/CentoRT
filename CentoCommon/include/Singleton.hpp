#pragma once
#include <memory>

namespace CentoCommon {
	template<typename T>
	class Singleton {
		static std::unique_ptr<T> _instance;

	public:
		static T* GetInstance() {
			if (!_instance) {
				_instance = std::make_unique<T>();
			}

			return _instance.get();
		}
	};

	template<typename T>
	inline std::unique_ptr<T> Singleton<T>::_instance = nullptr;
}

