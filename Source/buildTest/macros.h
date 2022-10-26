#pragma once
#include "Engine/GameEngine.h"

#define PRINT_X(x, ...) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT(x), __VA_ARGS__));}
#define PRINT(x) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT(x));}
