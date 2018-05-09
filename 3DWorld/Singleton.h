#pragma once

template<class T>
class Singleton
{
private:
	static T* m_Instance;

public:
	Singleton() {}
	~Singleton() {
		if (m_Instance)
			SafeDelete(m_Instance);
	}

public:
	static T* GetInstance()
	{
		if (m_Instance == nullptr)
			m_Instance = new T();

		return m_Instance;
	}

	static void Release()
	{
		if (m_Instance)
			SafeDelete(m_Instance);
	}

};

template<class T>
T* Singleton<T>::m_Instance = nullptr;