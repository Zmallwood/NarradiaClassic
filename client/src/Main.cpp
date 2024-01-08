int main(int argc, char *argv[]) {
    using namespace Narradia;

    while (Engine::get()->is_running()) {
        if (FPSCapper::get()->Below60FPS()) {
            try {
                EngineC::get()->HandleInput();
                EngineC::get()->UpdateGameFlow();
                Engine::get()->UpdateGameLogic();
                EngineV::get()->Render();
                Engine::get()->Finalize();
            } catch (Exception &e) {
                Console::get()->Print("Exception in main: " + String(e.what()));
            }
        }
    }

    DisposeSingletons();
}
