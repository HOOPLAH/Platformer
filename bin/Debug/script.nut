class Potion extends Item
{
    constructor()
    {
        base.constructor();
        setName("Potion");
    }

    function use()
    {
        base.use();
        print("used");
        //player.setHealth(player.getHealth() + 5);
    }
}

potion <- Potion();
potion.use();
//playerInventory.push_back(potion);
