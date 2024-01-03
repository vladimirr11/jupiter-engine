#pragma once

// Includes to be used by Jupiter application
// Base includes
#include "base/Application.h"
#include "base/Assert.h"
#include "base/Defines.h"
#include "base/Input.h"
#include "base/Logger.h"
#include "base/Timer.h"

// Cameras
#include "cameras/OrthographicCamera.h"

// Event system
#include "events/KeyboardEvents.h"
#include "events/MouseEvents.h"
#include "events/WindowEvents.h"

// Maths
#include "math/matrix/Transform.h"
#include "math/vector/Vector.h"

// Renderer
#include "renderer/IndexBuffer.h"
#include "renderer/Renderer.h"
#include "renderer/Shader.h"
#include "renderer/VertexArray.h"
#include "renderer/VertexBuffer.h"

// UI
#include "ui/imgui/ImGuiUiLayer.h"

// Entry point
#include "base/Entry.h"
