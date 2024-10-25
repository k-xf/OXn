#pragma once

UENUM()
enum class ECharacterState : uint8
{
	Idle,
	Jump,
};

class test
{
public:
	test()
	{
		AOxnCharacter d;

		d.OnCharacterStateChanged.Broadcast(0, 0);
	}
};