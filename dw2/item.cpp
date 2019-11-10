#include "main.h"

const itemi bsmeta<itemi>::elements[] = {{"Empthy", "Пусто"},
// Оружие
{"RaggedBow", "Потрепанный лук", 15, Moderate, Weapons, {Weight2, Near}, NoItem, Arrows},
{"FineBow", "Хороший лук", 60, Wealthy, Weapons, {Weight2, Near, Far}, NoItem, Arrows},
{"HuntersBow", "Охотничий лук", 100, Wealthy, Weapons, {Weight1, Near, Far}, NoItem, Arrows},
{"Crossbow", "Арбалет", 35, Rich, Weapons, {Weight1, Weight2, Near, DamageP1, Reloaded}},
{"BundleOfArrows", "Стрелы", 1, Moderate, Weapons, {Weight1, Ammo1, Ammo2}, Arrows},
{"ElvenArrows", "Эльфийские стрелы", 20, Rich, Weapons, {Weight1, Ammo4}, Arrows},
{"Club", "Дубинка", 1, Moderate, Weapons, {Weight2, Close}},
{"Staff", "Посох", 1, Moderate, Weapons, {Weight1, Close, TwoHanded}},
{"Knife", "Нож", 2, Moderate, Weapons, {Weight1, Hand}},
{"ThrowingDagger", "Метательный нож", 2, Moderate, Weapons, {Thrown, Near}},
{"ShortSword", "Короткий меч", 8, Moderate, Weapons, {Weight1, Close}},
{"Mace", "Булава", 8, Moderate, Weapons, {Weight1, Close}},
{"Warhammer", "Молот", 8, Moderate, Weapons, {Weight1, Close}},
{"Spear", "Копье", 5, Moderate, Weapons, {Weight1, Thrown, Reach, Near}},
{"LongSword", "Длинный меч", 15, Wealthy, Weapons, {Weight2, Close, DamageP1}},
{"Halberd", "Алебарда", 9, Rich, Weapons, {Weight2, DamageP1, TwoHanded, Reach}},
{"Rapier", "Рапира", 25, Wealthy, Weapons, {Precise, Close, Weight1}},
{"DuelingRapier", "Рапира дулянта", 50, Rich, Weapons, {Pierce1, Precise, Close, Weight2}},
//
{"FineClothing", "Роскошная одежда", 10, Wealthy, Weapons, {}},
{"Leather", "Кожанная броня", 10, Moderate, Weapons, {Weight1, Armor1}},
{"Chainmail", "Кольчуга", 10, Wealthy, Weapons, {Weight1, Armor1}},
{"Scalemail", "Чешуйчатый доспех", 50, Wealthy, Weapons, {Weight1, Weight2, Clumsy, Armor2}},
{"Plate", "Латный доспех", 350, Rich, Weapons, {Weight4, Clumsy, Armor1, Armor2}},
{"Shield", "Щит", 15, Moderate, Weapons, {Weight2, ArmorP1}},
//
{"AdventuringGear", "Снаряжение для приключений", 20, Poor, Tools, {Weight1, Use4, Use1}},
{"Bandages", "Бинты", 5, Poor, Tools, {Slow, Use2, Use1}},
{"Herbs", "Травы и припарки", 10, Poor, Species, {Weight1, Slow, Use2}},
{"HealingPotion", "Лечебное зелье", 50, Wealthy, Potions},
{"KegOfDwarvenStout", "Боченок Дварфийского Алкоголя", 10, Rich, Species, {Weight4}},
{"BagOfBooks", "Сумка с книгами", 10, Wealthy, Tools, {Weight2, Use4, Use1}},
{"Antitoxin", "Антитоксин", 10, Rich, Potions},
//
{"DungeonRation", "Сухпаек", 3, Poor, Foods, {Weight1, Ration, Use1, Use4}},
{"PersonalFeast", "Шикарная еда", 10, Wealthy, Foods, {Weight1, Ration, Use1}},
{"DwarvenHardtack", "Сухари дварфов", 3, Wealthy, Foods, {Weight1, Ration, Use1, Use4, Use2}},
{"ElvenBread", "Эльфийский хлеб", 10, Wealthy, Foods, {Weight1, Ration, Use1, Use4, Use2}},
{"HalflingPipeleaf", "Пирог хоббитов", 5, Rich, Foods, {Ration, Use1}},
//
{"Mandoline", "Мандолина", 40, Rich, Tools},
{"Lute", "Лютня", 40, Rich, Tools},
{"Pipes", "Свирель", 40, Rich, Tools},
//
{"HolySymbol", "Святой символ", 5, Wealthy, Tools},
{"SpellBook", "Книга заклинаний", 5, Wealthy, Tools},
//
{"Bloodstone", "Кроваый камень", 5, Moderate, Gems},
{"Chrysoprase", "Хризопраз", 5, Moderate, Gems},
{"Iolite", "Иолит", 5, Moderate, Gems},
{"Jasper", "Джаспер", 5, Moderate, Gems},
{"Moonstone", "Лунный камень", 5, Moderate, Gems},
{"Onyx", "Оникс", 5, Moderate, Gems},
// Улики
{"Map", "Карта", 5, Moderate, Clues},
{"Note", "Заметки", 5, Moderate, Clues},
{"Journal", "Дневник", 5, Moderate, Clues},
// Драгоценности
{"Alexandrite", "Александрит", 5, Rich, Gems},
{"Aquamarine", "Аквамарин", 5, Rich, Gems},
{"Black Pearl", "Черная жемчужина", 5, Rich, Gems},
{"Topaz", "Топаз", 5, Rich, Gems},
//
{"Poison", "Яд", 5, Wealthy, Potions},
//
{"SilverCoins", "Серебрянные Монеты", 1, Dirt, Gems},
{"GoldCoins", "Золотые Монеты", 10, Dirt, Gems},
};