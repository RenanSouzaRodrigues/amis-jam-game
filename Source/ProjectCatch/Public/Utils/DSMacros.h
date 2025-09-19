
#pragma once

#define DS_LOG_ERROR(message) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, message)
#define DS_LOG_ERROR_TICK(message) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, message)
#define DS_LOG_WARN(message) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Orange, message)
#define DS_LOG_WARN_TICK(message) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Orange, message)
#define DS_LOG_INFO(message) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, message)
#define DS_LOG_INFO_TICK(message) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Cyan, message)
#define DS_LOG_SUCCESS(message) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, message)
#define DS_LOG_SUCCESS_TICK(message) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Green, message)