#pragma once

class App {
public:
	App() = delete;

	static void Run();

	static void Draw();
	static void Update();
	static void Init();

private:
	static bool running_;
};