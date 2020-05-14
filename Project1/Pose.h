#pragma once
#define lpPose Pose::GetInstance()
class Pose
{
public:
	static Pose& GetInstance()
	{
		static Pose s_Incetance;
		return s_Incetance;
	}
	void Draw(bool Optionflag);
private:
	Pose();
	~Pose();
};

