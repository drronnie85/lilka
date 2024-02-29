-- Character sprites by https://laredgames.itch.io/coins-free

WHITE = display.color565(255, 255, 255)
BLACK = display.color565(0, 0, 0)

ROOT = 'runner/'

PlayerState = {
    STAND = "stand",
    RUN = "run",
    JUMP = "jump",
}

Player = {
    x = 32,
    y = 128,
    width = 32, -- Розмір спрайту - 32x32
    height = 32,
    sprites = {
        -- stand = { resources.load_bitmap(ROOT .. "boy_stand.bmp") },
        stand = { resources.load_bitmap("face.bmp", BLACK) },
        run = {
            resources.load_bitmap(ROOT .. "boy_run_1.bmp", BLACK),
            resources.load_bitmap(ROOT .. "boy_run_2.bmp", BLACK),
            resources.load_bitmap(ROOT .. "boy_run_3.bmp", BLACK),
        },
        jump = { resources.load_bitmap(ROOT .. "boy_jump.bmp", BLACK) },
    },
    state = PlayerState.RUN,
}

function Player:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

function Player:update(delta)
    self.x = self.x + 50 * delta
end

function Player:draw()
    local bitmap
    if self.state == PlayerState.STAND then
        bitmap = self.sprites.stand[1]
    elseif self.state == PlayerState.RUN then
        -- Перемикаємо спрайти бігу кожні 0.25 секунди
        bitmap = self.sprites.run[math.floor(util.time() * 4) % #self.sprites.run + 1]
    elseif self.state == PlayerState.JUMP then
        bitmap = self.sprites.jump[1]
    end
    -- Малюємо гравця на екрані так, щоб середина нижнього краю спрайту була в координатах (x, y)
    display.draw_bitmap(bitmap, self.x - self.width / 2, self.y - self.height)
end

local player = Player:new({ x = 128, y = 128 })

display.fill_screen(BLACK)
display.render()

function lilka._update(delta)
    player:update(delta)
    player:draw()
    display.render()
end
