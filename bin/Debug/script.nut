class Weapon extends Item
{
    constructor()
    {
        base.constructor();
        setName("Weapon");
    }

    function use()
    {
        base.use();
        print(getCount()+"\n");
    }
}
