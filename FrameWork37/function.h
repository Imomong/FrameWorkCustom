#pragma once

template <typename T>
inline void Safe_Delete(T& Temp)
{
	if(Temp)
	{
		delete Temp;
		Temp = NULL;
	}
}