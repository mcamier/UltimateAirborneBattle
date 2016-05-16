function useDummyObject(dummy)
    local x = dummy:getX()
    print("[LUA] x = "..dummy:getX())
    print("[LUA] y = "..dummy:getY())
    dummy:setX(45);
    dummy:setY(dummy:getY() + 1000);
end

obj = {
    aBool = true,
    aString = "this is a string",
    aInteger = 154,
    aFloat = 0.54
}

entity = {
    CPosition = {
        x = 10,
        y = 100
    },
    CSprite = {
        alpha = 0.5,
        resourceID = 1
    }
}