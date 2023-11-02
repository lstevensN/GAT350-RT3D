#include "World01.h"
#include "World02.h"
#include "World03.h"
#include "World04.h"
#include "World05.h"
#include "Core/Core.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"

using namespace std;

int main(int argc, char* argv[])
{
	INFO_LOG("Initialize Engine...")

	// nc::MemoryTracker::Initialize();
	nc::seedRandom((unsigned int)time(nullptr));
	nc::setFilePath("assets");

	ENGINE.Initialize();

	auto world = make_unique<nc::World05>();
	world->Initialize();


	/*std::string test = "BinGus";
	std::string phrase = "Bingus is Best";

	std::cout << nc::StringUtils::ToLower(test) << std::endl;
	std::cout << nc::StringUtils::ToUpper(test) << std::endl;
	std::cout << nc::StringUtils::IsEqualIgnoreCase(test, phrase) << std::endl;

	std::cout << nc::StringUtils::CreateUnique(phrase) << std::endl;
	std::cout << nc::StringUtils::CreateUnique(phrase) << std::endl;
	std::cout << nc::StringUtils::CreateUnique(phrase) << std::endl;
	std::cout << nc::StringUtils::CreateUnique(phrase) << std::endl;
	std::cout << nc::StringUtils::CreateUnique(phrase) << std::endl;*/


	// main loop
	bool quit = false;
	while (!quit)
	{
		// update
		ENGINE.Update();
		quit = ENGINE.IsQuit();

		world->Update(ENGINE.GetTime().GetDeltaTime());

		// draw
		world->Draw(*ENGINE.GetSystem<nc::Renderer>());
	}

	world->Shutdown();
	ENGINE.Shutdown();

	return 0;
}
