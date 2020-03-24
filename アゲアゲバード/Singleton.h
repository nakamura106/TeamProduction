#ifndef SINGLETON_H_
#define SINGLETON_H_

// Template_Class
template<class T>
class Singleton {
	// �V���O���g���f�U�C���p�^�[��
public:
	// ���̂����֐�
	static void CreateInstance()
	{
		if (CheckNull() == true)
		{
			p_Instance = new T();
		}
	}

	// ���̂�j������֐�
	static void DestroyInstance()
	{
		if (!CheckNull() == false)
		{
			delete p_Instance;
			p_Instance = nullptr;
		}
	}

	// ���̂����݂��邩�m�F����֐�
	static bool CheckNull()
	{
		return p_Instance == nullptr;
	}

	// ���̂��擾����֐�
	static T* GetInstance()
	{
		return p_Instance;
	}

protected:
	Singleton() {}		// �R���X�g���N�^�}��
	~Singleton() {}		// �f�X�g���N�^�}��

private:
	static T* p_Instance;	// �������g�̗B��̎���

};

// static�ȃ����o�ϐ���������
template<class T>
T* Singleton<T>::p_Instance = nullptr;

#endif