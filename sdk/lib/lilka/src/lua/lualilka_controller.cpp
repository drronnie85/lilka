#include "lualilka_controller.h"

namespace lilka {

int lualilka_controller_getState(lua_State* L) {
    State state = controller.getState();
    lua_createtable(L, 0, 10);
    // Push up, down, left, right, a, b, c, d, select, start to the table
    const char* keys[] = {"up", "down", "left", "right", "a", "b", "c", "d", "select", "start"};
    for (int i = 0; i < 10; i++) {
        lua_pushstring(L, keys[i]);
        // Push value as table with keys {pressed, just_pressed, just_released}
        lua_createtable(L, 0, 2);
        lua_pushstring(L, "pressed");
        lua_pushboolean(L, state.buttons[i].pressed);
        lua_settable(L, -3);
        lua_pushstring(L, "just_pressed");
        lua_pushboolean(L, state.buttons[i].justPressed);
        lua_settable(L, -3);
        lua_pushstring(L, "just_released");
        lua_pushboolean(L, state.buttons[i].justReleased);
        lua_settable(L, -3);
        lua_settable(L, -3);
    }

    // Return table
    return 1;
}

static const luaL_Reg lualilka_controller[] = {
    {"get_state", lualilka_controller_getState},
    {NULL, NULL},
};

int luaopen_lilka_controller(lua_State* L) {
    luaL_newlib(L, lualilka_controller);
    return 1;
}

} // namespace lilka