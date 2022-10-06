#pragma once

#include <memory>
#include "Input.h"
#include "DebugText.h"

class door
{
public:

	door();

	~door();

	// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	bool mashFlag_ = false;
	UINT mashNum_ = 0;
private:

	/// <summary>
	/// �A�ŏ���
	/// </summary>
	void Mash();

	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;
};

