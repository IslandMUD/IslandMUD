/* Jim Viebke
Feb 16 2015 */

#include "parse.h"

std::map<std::string, std::string> Parse::dict; // first string maps to second string

void Parse::initialize()
{
	// map various possible user-input strings to the constant ID used throughout the engine

	using P = Parse;

	if (dict.size() == 0)
	{
		std::cout << "\nLoading parse dictionary...";

		// test commands
		P::dict["recipe"] = P::dict["recipes"] = C::PRINT_RECIPES_COMMAND;

		// verbs
		P::dict["help"] = P::dict["h"] = P::dict["q"] = P::dict["?"] = P::dict["assist"] = P::dict["command"] = P::dict["commands"] = C::SHOW_HELP_COMMAND;
		P::dict["legend"] = C::LEGEND_COMMAND;
		P::dict["i"] = P::dict["inv"] = P::dict["inventory"] = C::INVENTORY_COMMAND;
		P::dict["l"] = P::dict["look"] = C::LOOK_COMMAND;
		P::dict["save"] = P::dict["logout"] = P::dict["quit"] = P::dict["leave"] = P::dict["exit"] = C::SAVE_COMMAND;
		P::dict["move"] = P::dict["m"] = P::dict["walk"] = P::dict["run"] = P::dict["head"] = P::dict["go"] = P::dict["continue"] = P::dict["work"] = C::MOVE_COMMAND;
		P::dict["take"] = P::dict["get"] = P::dict["pick"] = P::dict["choose"] = P::dict["grab"] = P::dict["acquire"] = C::TAKE_COMMAND;
		P::dict["equip"] = P::dict["equipped"] = P::dict["weild"] = P::dict["wield"] = P::dict["ready"] = P::dict["draw"] = C::EQUIP_COMMAND;
		P::dict["item"] = C::ITEM_COMMAND; // viewing equipped item
		P::dict["dequip"] = P::dict["deequip"] = P::dict["unequip"] = P::dict["unwield"] = P::dict["unweild"] = P::dict["store"] = P::dict["sheathe"] = P::dict["sheath"] = P::dict["lower"] = C::DEQUIP_COMMAND;
		P::dict["craft"] = P::dict["make"] = P::dict["create"] = P::dict["fashion"] = C::CRAFT_COMMAND;
		P::dict["mine"] = C::MINE_COMMAND;
		P::dict["drop"] = P::dict["release"] = P::dict["unhand"] = P::dict["add"] = P::dict["place"] = P::dict["put"] = C::DROP_COMMAND;
		P::dict["into"] = P::dict["in"] = P::dict["to"] = P::dict["within"] = P::dict["on"] = P::dict["onto"] = C::INSERT_COMMAND;
		P::dict["from"] = P::dict["form"] = C::FROM_COMMAND;
		P::dict["with"] = C::WITH_COMMAND;
		P::dict["construct"] = P::dict["build"] = P::dict["erect"] = C::CONSTRUCT_COMMAND;
		P::dict["attack"] = P::dict["smash"] = P::dict["strike"] = P::dict["bash"] = P::dict["break"] = P::dict["damage"] = P::dict["stab"] = P::dict["slash"] = P::dict["chop"] = C::ATTACK_COMMAND;

		// quantity
		P::dict["all"] = P::dict["each"] = P::dict["every"] = P::dict["*"] = C::ALL_COMMAND;

		// items

		// items -> other
		P::dict["bloom"] = P::dict["blooms"] = C::BLOOM_ID;
		P::dict["bloomery"] = P::dict["bloomeries"] = C::BLOOMERY_ID;
		P::dict["forge"] = P::dict["forges"] = C::FORGE_ID;
		P::dict["anvil"] = P::dict["anvils"] = C::ANVIL_ID;
		P::dict["tree"] = P::dict["trees"] = C::TREE_ID;
		P::dict["chest"] = P::dict["chests"] = P::dict["crate"] = P::dict["crates"] = C::CHEST_ID;
		P::dict["log"] = P::dict["logs"] = C::LOG_ID;

		// items -> stackables
		P::dict["stone"] = P::dict["stones"] = P::dict["rock"] = P::dict["rocks"] = C::STONE_ID;
		P::dict["branch"] = P::dict["branches"] = C::BRANCH_ID;
		P::dict["stick"] = P::dict["sticks"] = C::STICK_ID;
		P::dict["vine"] = P::dict["vines"] = C::VINE_ID;
		P::dict["arrow"] = P::dict["arrows"] = C::ARROW_ID;
		P::dict["arrowhead"] = P::dict["arrowheads"] = C::ARROWHEAD_ID;
		P::dict["board"] = P::dict["boards"] = P::dict["plank"] = P::dict["planks"] = C::BOARD_ID;

		// items -> tools
		P::dict["bow"] = P::dict["bows"] = C::BOW_ID;
		P::dict["staff"] = P::dict["staffs"] = C::STAFF_ID;
		P::dict["axe"] = P::dict["axes"] = P::dict["ax"] = P::dict["axs"] = C::AXE_ID;
		P::dict["sword"] = P::dict["swords"] = C::SWORD_ID;
		P::dict["hammer"] = P::dict["hammers"] = C::HAMMER_ID;

		// items -> minerals
		P::dict["iron"] = P::dict["irons"] = C::IRON_ID;
		P::dict["limestone"] = P::dict["limestones"] = C::LIMESTONE_ID;

		// items -> mineral keywords (partial IDs for compound mineral names)
		P::dict["deposit"] = C::KEYWORD_DEPOSIT;

		// directions
		P::dict["n"] = P::dict["north"] = C::NORTH;
		P::dict["ne"] = P::dict["northeast"] = C::NORTH_EAST;
		P::dict["e"] = P::dict["east"] = C::EAST;
		P::dict["se"] = P::dict["southeast"] = C::SOUTH_EAST;
		P::dict["s"] = P::dict["south"] = C::SOUTH;
		P::dict["sw"] = P::dict["southwest"] = C::SOUTH_WEST;
		P::dict["w"] = P::dict["west"] = C::WEST;
		P::dict["nw"] = P::dict["northwest"] = C::NORTH_WEST;
		P::dict["u"] = P::dict["up"] = P::dict["upward"] = P::dict["upwards"] = P::dict["upstairs"] = C::UP;
		P::dict["d"] = P::dict["down"] = P::dict["downward"] = P::dict["downwards"] = P::dict["downstairs"] = C::DOWN;

		// surfaces not already in directions
		P::dict["floor"] = P::dict["ground"] = C::FLOOR;
		P::dict["ceiling"] = C::CEILING;

		// Look Mr. Frodo! A
		P::dict["door"] = C::DOOR;
		P::dict["wall"] = P::dict["surface"] = C::WALL;

		std::stringstream ss;
		ss << "\nLoaded parse dictionary with " << P::dict.size() << " entries.";
		std::cout << ss.str();
	}
}

std::vector<std::string> Parse::tokenize(const std::string & s)
{
	// converts an input string to vector of "engine official" keywords/commands

	if (Parse::dict.size() == 0) Parse::initialize();

	// convert the space-delimited user input to a vector of strings (one word per string)
	std::stringstream input_stream(s);
	const std::istream_iterator<std::string> begin(input_stream);
	std::vector<std::string> strings(begin, std::istream_iterator<std::string>());

	{
		std::stringstream ss;
		ss << "Parse::tokenize: ";
		for (const auto & s : strings) ss << s << " ";
		ss << '\n';
		std::cout << ss.str();
	}

	for (std::string & word : strings) // for each word
	{
		// convert the word to lowercase
		U::to_lower_case(word);

		// replace the typed word with the engine keyword if one exists
		const std::map<std::string, std::string>::const_iterator dict_it = dict.find(word);
		if (dict_it != dict.cend())
		{
			word = dict_it->second;
		}
	}

	return strings;
}
