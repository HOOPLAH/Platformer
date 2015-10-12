class Weapon extends Item
{
    constructor()
    {
        base.constructor();
        setName("Weapon");

        mFirePoint = Vector2f(10.0, 0.0);
    }

    function use()
    {
        //base.use();
        worldRef.addProjectile(playerPosition, 10, 500, 0, player.getWeaponAngle());
    }

    function update()
    {
        base.update();
        //print(playerPosition.x+"\n");
    }

    mFirePoint = null;
}
