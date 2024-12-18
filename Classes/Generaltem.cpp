#include "Generaltem.h"

// 动物设定为购买后直接加入牧场，在背包中不可见

// 动物  
Item AnimalChicken ( "AnimalChicken" , "Item/Surpermarket/Animal/Brown_Chicken.png" , 4000 , 99 );
Item AnimalDuck ( "AnimalDuck" , "Item/Surpermarket/Animal/Duck.png" , 1200 , 99 );
Item AnimalGoat ( "AnimalGoat" , "Item/Surpermarket/Animal/Goat.png" , 4000 , 99 );
Item AnimalPig ( "AnimalPig" , "Item/Surpermarket/Animal/Pig.png" , 16000 , 99 );
Item AnimalRabbit ( "AnimalRabbit" , "Item/Surpermarket/Animal/Rabbit.png" , 800 , 99 );
Item AnimalSheep ( "AnimalSheep" , "Item/Surpermarket/Animal/Sheep.png" , 8000 , 99 );
Item AnimalCow ( "AnimalCow" , "Item/Surpermarket/Animal/White_Cow.png" , 800 , 99 );

// 春季种子物品列表  
Item Bean_Starter ( "Bean_Starter" , "Item/Surpermarket/Spring/Bean_Starter.png" , 60 , 99 );
Item Carrot_Seeds ( "Carrot_Seeds" , "Item/Surpermarket/Spring/Carrot_Seeds.png" , 100 , 99 );
Item Cauliflower_Seeds ( "Cauliflower_Seeds" , "Item/Surpermarket/Spring/Cauliflower_Seeds.png" , 100 , 99 );
Item Coffee_Bean ( "Coffee_Bean" , "Item/Surpermarket/Spring/Coffee_Bean.png" , 250 , 99 );
Item Garlic_Seeds ( "Garlic_Seeds" , "Item/Surpermarket/Spring/Garlic_Seeds.png" , 40 , 99 );
Item Jazz_Seeds ( "Jazz_Seeds" , "Item/Surpermarket/Spring/Jazz_Seeds.png" , 100 , 99 );
Item Kale_Seeds ( "Kale_Seeds" , "Item/Surpermarket/Spring/Kale_Seeds.png" , 70 , 99 );
Item Parsnip_Seeds ( "Parsnip_Seeds" , "Item/Surpermarket/Spring/Parsnip_Seeds.png" , 20 , 99 );
Item Potato_Seeds ( "Potato_Seeds" , "Item/Surpermarket/Spring/Potato_Seeds.png" , 50 , 99 );
Item Rhubarb_Seeds ( "Rhubarb_Seeds" , "Item/Surpermarket/Spring/Rhubarb_Seeds.png" , 100 , 99 );
Item Rice_Shoot ( "Rice_Shoot" , "Item/Surpermarket/Spring/Rice_Shoot.png" , 20 , 99 );
Item Strawberry_Seeds ( "Strawberry_Seeds" , "Item/Surpermarket/Spring/Strawberry_Seeds.png" , 100 , 99 );
Item Tulip_Bulb ( "Tulip_Bulb" , "Item/Surpermarket/Spring/Tulip_Bulb.png" , 20 , 99 );

// 夏季种子物品列表  
Item Amaranth_Seeds ( "Amaranth_Seeds" , "Item/Surpermarket/Summer/Amaranth_Seeds.png" , 70 , 99 );
Item Artichoke_Seeds ( "Artichoke_Seeds" , "Item/Surpermarket/Summer/Artichoke_Seeds.png" , 30 , 99 );
Item Beet_Seeds ( "Beet_Seeds" , "Item/Surpermarket/Summer/Beet_Seeds.png" , 100 , 99 );
Item Blueberry_Seeds ( "Blueberry_Seeds" , "Item/Surpermarket/Summer/Blueberry_Seeds.png" , 80 , 99 );
Item Bok_Choy_Seeds ( "Bok_Choy_Seeds" , "Item/Surpermarket/Summer/Bok_Choy_Seeds.png" , 50 , 99 );
Item Broccoli_Seeds ( "Broccoli_Seeds" , "Item/Surpermarket/Summer/Broccoli_Seeds.png" , 80 , 99 );
Item Corn_Seeds ( "Corn_Seeds" , "Item/Surpermarket/Summer/Corn_Seeds.png" , 100 , 99 );
Item Cranberry_Seeds ( "Cranberry_Seeds" , "Item/Surpermarket/Summer/Cranberry_Seeds.png" , 240 , 99 );
Item Eggplant_Seeds ( "Eggplant_Seeds" , "Item/Surpermarket/Summer/Eggplant_Seeds.png" , 20 , 99 );
Item Fairy_Seeds ( "Fairy_Seeds" , "Item/Surpermarket/Summer/Fairy_Seeds.png" , 100 , 99 );
Item Grape_Starter ( "Grape_Starter" , "Item/Surpermarket/Summer/Grape_Starter.png" , 60 , 99 );
Item Hops_Starter ( "Hops_Starter" , "Item/Surpermarket/Summer/Hops_Starter.png" , 100 , 99 );
Item Melon_Seeds ( "Melon_Seeds" , "Item/Surpermarket/Summer/Melon_Seeds.png" , 80 , 99 );
Item Pepper_Seeds ( "Pepper_Seeds" , "Item/Surpermarket/Summer/Pepper_Seeds.png" , 40 , 99 );
Item Poppy_Seeds ( "Poppy_Seeds" , "Item/Surpermarket/Summer/Poppy_Seeds.png" , 100 , 99 );
Item Pumpkin_Seeds ( "Pumpkin_Seeds" , "Item/Surpermarket/Summer/Pumpkin_Seeds.png" , 100 , 99 );
Item Radish_Seeds ( "Radish_Seeds" , "Item/Surpermarket/Summer/Radish_Seeds.png" , 40 , 99 );
Item Red_Cabbage_Seeds ( "Red_Cabbage_Seeds" , "Item/Surpermarket/Summer/Red_Cabbage_Seeds.png" , 100 , 99 );
Item Spangle_Seeds ( "Spangle_Seeds" , "Item/Surpermarket/Summer/Spangle_Seeds.png" , 100 , 99 );
Item Starfruit_Seeds ( "Starfruit_Seeds" , "Item/Surpermarket/Summer/Starfruit_Seeds.png" , 400 , 99 );
Item Summer_Squash_Seeds ( "Summer_Squash_Seeds" , "Item/Surpermarket/Summer/Summer_Squash_Seeds.png" , 50 , 99 );
Item Sunflower_Seeds ( "Sunflower_Seeds" , "Item/Surpermarket/Summer/Sunflower_Seeds.png" , 200 , 99 );
Item Tomato_Seeds ( "Tomato_Seeds" , "Item/Surpermarket/Summer/Tomato_Seeds.png" , 50 , 99 );
Item Wheat_Seeds ( "Wheat_Seeds" , "Item/Surpermarket/Summer/Wheat_Seeds.png" , 100 , 99 );
Item Yam_Seeds ( "Yam_Seeds" , "Item/Surpermarket/Summer/Yam_Seeds.png" , 60 , 99 );

// 冬季种子物品列表  
Item Powdermelon_Seeds ( "Powdermelon_Seeds" , "Item/Surpermarket/Summer/Powdermelon_Seeds.png" , 1 , 99 ); // 请注意，游戏中没有冬季种子这个物品  

// 工具列表  
Item Backpack_36 ( "36_Backpack" , "Item/Surpermarket/Tools/36_Backpack.png" , 2000 , 99 );
Item Backpack ( "Backpack" , "Item/Surpermarket/Tools/Backpack.png" , 2000 , 99 );
Item Advanced_Iridium_Rod ( "Advanced_Iridium_Rod" , "Item/Surpermarket/Tools/Advanced_Iridium_Rod.png" , 2000 , 99 );
Item Axe ( "Axe" , "Item/Surpermarket/Tools/Axe.png" , 200 , 99 );
Item Bamboo_Pole ( "Bamboo_Pole" , "Item/Surpermarket/Tools/Bamboo_Pole.png" , 200 , 99 );
Item Copper_Axe ( "Copper_Axe" , "Item/Surpermarket/Tools/Copper_Axe.png" , 900 , 99 );
Item Copper_Hoe ( "Copper_Hoe" , "Item/Surpermarket/Tools/Copper_Hoe.png" , 900 , 99 );
Item Copper_Pan ( "Copper_Pan" , "Item/Surpermarket/Tools/Copper_Pan.png" , 200 , 99 );
Item Copper_Pickaxe ( "Copper_Pickaxe" , "Item/Surpermarket/Tools/Copper_Pickaxe.png" , 900 , 99 );
Item Copper_Watering ( "Copper_Watering" , "Item/Surpermarket/Tools/Copper_Watering.png" , 900 , 99 );
Item Fiberglass_Rod ( "Fiberglass_Rod" , "Item/Surpermarket/Tools/Fiberglass_Rod.png" , 1800 , 99 );
Item Gold_Axe ( "Gold_Axe" , "Item/Surpermarket/Tools/Gold_Axe.png" , 4000 , 99 );
Item Gold_Hoe ( "Gold_Hoe" , "Item/Surpermarket/Tools/Gold_Hoe.png" , 4000 , 99 );
Item Gold_Pan ( "Gold_Pan" , "Item/Surpermarket/Tools/Gold_Pan.png" , 2000 , 99 );
Item Gold_Pickaxe ( "Gold_Pickaxe" , "Item/Surpermarket/Tools/Gold_Pickaxe.png" , 4000 , 99 );
Item Gold_Watering_Can ( "Gold_Watering_Can" , "Item/Surpermarket/Tools/Gold_Watering_Can.png" , 4000 , 99 );
Item Golden_Scythe ( "Golden_Scythe" , "Item/Surpermarket/Tools/Golden_Scythe.png" , 1000 , 99 );
Item Hoe ( "Hoe" , "Item/Surpermarket/Tools/Hoe.png" , 200 , 99 );
Item Pickaxe ( "Pickaxe" , "Item/Surpermarket/Tools/Pickaxe.png" , 200 , 99 );
Item Milk_Pail ( "Milk_Pail" , "Item/Surpermarket/Tools/Milk_Pail.png" , 200 , 99 );
Item Scythe ( "Scythe" , "Item/Surpermarket/Tools/Scythe.png" , 200 , 99 );
Item Steel_Axe ( "Steel_Axe" , "Item/Surpermarket/Tools/Steel_Axe.png" , 2000 , 99 );
Item Steel_Hoe ( "Steel_Hoe" , "Item/Surpermarket/Tools/Steel_Hoe.png" , 2000 , 99 );
Item Steel_Pan ( "Steel_Pan" , "Item/Surpermarket/Tools/Steel_Pan.png" , 2000 , 99 );
Item Steel_Pickaxe ( "Steel_Pickaxe" , "Item/Surpermarket/Tools/Steel_Pickaxe.png" , 2000 , 99 );
Item Steel_Watering ( "Steel_Watering" , "Item/Surpermarket/Tools/Steel_Watering.png" , 2000 , 99 );
Item Trash_Can_Copper ( "Trash_Can_Copper" , "Item/Surpermarket/Tools/Trash_Can_Copper.png" , 250 , 99 );
Item Watering_Can ( "Watering_Can" , "Item/Surpermarket/Tools/Watering_Can.png" , 200 , 99 );
Item Trash_Can_Steel ( "Trash_Can_Steel" , "Item/Surpermarket/Tools/Trash_Can_Steel.png" , 500 , 99 );

// 树苗列表  
Item Apple_Sapling ( "Apple_Sapling" , "Item/Surpermarket/Tree/Apple_Sapling.png" , 1000 , 99 );
Item Apricot_Sapling ( "Apricot_Sapling" , "Item/Surpermarket/Tree/Apricot_Sapling.png" , 2000 , 99 );
Item Banana_Sapling ( "Banana_Sapling" , "Item/Surpermarket/Tree/Banana_Sapling.png" , 2000 , 99 );
Item Cherry_Sapling ( "Cherry_Sapling" , "Item/Surpermarket/Tree/Cherry_Sapling.png" , 3000 , 99 );
Item Mango_Sapling ( "Mango_Sapling" , "Item/Surpermarket/Tree/Mango_Sapling.png" , 2000 , 99 );
Item Orange_Sapling ( "Orange_Sapling" , "Item/Surpermarket/Tree/Orange_Sapling.png" , 2000 , 99 );
Item Peach_Sapling ( "Peach_Sapling" , "Item/Surpermarket/Tree/Peach_Sapling.png" , 3000 , 99 );
Item Pomegranate_Sapling ( "Pomegranate_Sapling" , "Item/Surpermarket/Tree/Pomegranate_Sapling.png" , 3000 , 99 );

// 宝石
Item amethyst("Amethyst", "Ore/Amethyst3.png", 1000, 99);
Item emerald("Emerald", "Ore/Emerald3.png", 1000, 99);
Item ruby("Ruby", "Ore/Ruby3.png", 1000, 99);

// 成熟作物
Item Wheat("wheat", "crop/wheat4.png", 1000, 99);
Item Corn("corn", "crop/corn4.png", 1000, 99);
Item Potato("potato", "crop/Potato4.png", 1000, 99);
Item Pumpkin("pumpkin", "crop/Pumpkin4.png", 1000, 99);
Item Blueberry("blueberry", "crop/blueberry4.png", 1000, 99);
Item Wood("wood", "tree/wood.png", 1000, 99);


