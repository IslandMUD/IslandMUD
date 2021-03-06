/* Jim Viebke
May 15 2015 */

#include "recipes.h"

Recipes::Recipes()
{
	load();
}

// information
bool Recipes::has_recipe_for(const std::string & name) const
{
	return this->recipes.find(name) != this->recipes.cend();
}

// retrieval
Recipe Recipes::get_recipe(const std::string & recipe_name) const
{
	return this->recipes.find(recipe_name)->second;
}

// debugging
std::string Recipes::get_recipes() const
{
	std::stringstream output;
	for (auto & recipe : recipes)
	{
		output << recipe.first << std::endl;
		if (recipe.second.inventory_need.size() > 0)
		{
			output << "\tRequired in inventory:\n";
			for (std::map<std::string, int>::const_iterator it = recipe.second.inventory_need.cbegin(); it != recipe.second.inventory_need.cend(); ++it)
			{
				output << "\t\t" << it->second << " " << it->first << std::endl; // 5 stick
			}
		}
		if (recipe.second.inventory_remove.size() > 0)
		{
			output << "\tUsed from inventory:\n";
			for (std::map<std::string, int>::const_iterator it = recipe.second.inventory_remove.cbegin(); it != recipe.second.inventory_remove.cend(); ++it)
			{
				output << "\t\t" << it->second << " " << it->first << std::endl; // 5 stick
			}
		}
		if (recipe.second.local_need.size() > 0)
		{
			output << "\tLocally required:\n";
			for (std::map<std::string, int>::const_iterator it = recipe.second.local_need.cbegin(); it != recipe.second.local_need.cend(); ++it)
			{
				output << "\t\t" << it->second << " " << it->first << std::endl; // 5 stick
			}
		}
		if (recipe.second.local_remove.size() > 0)
		{
			output << "\tLocally consumed:\n";
			for (std::map<std::string, int>::const_iterator it = recipe.second.local_remove.cbegin(); it != recipe.second.local_remove.cend(); ++it)
			{
				output << "\t\t" << it->second << " " << it->first << std::endl; // 5 stick
			}
		}
		output << std::endl;
	}
	return output.str();
}
std::string Recipes::get_recipes_matching(const std::string & item_ID) const
{
	std::stringstream output;
	for (auto & recipe : recipes)
	{
		// skip recipes that don't contain "item_ID" in the key
		if (recipe.first.find(item_ID) == std::string::npos)
			continue;

		output << recipe.first << std::endl;
		if (recipe.second.inventory_need.size() > 0)
		{
			output << "\tRequired in inventory:\n";
			for (std::map<std::string, int>::const_iterator it = recipe.second.inventory_need.cbegin(); it != recipe.second.inventory_need.cend(); ++it)
			{
				output << "\t\t" << it->second << " " << it->first << std::endl; // 5 stick
			}
		}
		if (recipe.second.inventory_remove.size() > 0)
		{
			output << "\tUsed from inventory:\n";
			for (std::map<std::string, int>::const_iterator it = recipe.second.inventory_remove.cbegin(); it != recipe.second.inventory_remove.cend(); ++it)
			{
				output << "\t\t" << it->second << " " << it->first << std::endl; // 5 stick
			}
		}
		if (recipe.second.local_need.size() > 0)
		{
			output << "\tLocally required:\n";
			for (std::map<std::string, int>::const_iterator it = recipe.second.local_need.cbegin(); it != recipe.second.local_need.cend(); ++it)
			{
				output << "\t\t" << it->second << " " << it->first << std::endl; // 5 stick
			}
		}
		if (recipe.second.local_remove.size() > 0)
		{
			output << "\tLocally consumed:\n";
			for (std::map<std::string, int>::const_iterator it = recipe.second.local_remove.cbegin(); it != recipe.second.local_remove.cend(); ++it)
			{
				output << "\t\t" << it->second << " " << it->first << std::endl; // 5 stick
			}
		}
		output << std::endl;
	}

	// copy the result to a string
	const std::string result = output.str();

	// if the result is not empty, return it, else return a message
	return ((result.size() > 0) ? result : "No recipes for \"" + item_ID + "\".");
}

void Recipes::load()
{
	/* arguments in order:
	recipe name
	map of item IDs that need to be in inventory
	map of item IDs that need to be in inventory, are removed
	map of item IDs that need to be in the room
	map of item IDs that need to be in the room, are removed
	map of item IDs to be yielded */

	std::cout << "\nLoading crafting recipes...";

	// add_recipe("recipe name", {}, {}, {}, {}, {});

	// materials
	add_recipe(C::STICK_ID, {}, {}, { { C::TREE_ID, 1 } }, {}, { { C::STICK_ID, 1 } });
	add_recipe(C::BRANCH_ID, {}, {}, { { C::TREE_ID, 1 } }, {}, { { C::BRANCH_ID, 1 } });
	add_recipe(C::VINE_ID, {}, {}, { { C::TREE_ID, 1 } }, {}, { { C::VINE_ID, 1 } });
	add_recipe(C::STONE_ID, {}, {}, {}, {}, { { C::STONE_ID, 1 } }); // you can always get a stone
	add_recipe(C::ARROW_ID, {}, { { C::ARROWHEAD_ID, 1 }, { C::STICK_ID, 1 } }, {}, {}, { { C::ARROW_ID, 1 } }); // a stick and an arrowhead
	add_recipe(C::ARROWHEAD_ID, { { C::STONE_ID, 2 } }, { { C::STONE_ID, 1 } }, {}, {}, { { C::ARROWHEAD_ID, 3 } }); // requires two stones but only one is made into arrowheads
	add_recipe(C::BOARD_ID, { { C::AXE_ID, 1 } }, {}, { { C::TREE_ID, 1 } }, {}, { { C::BOARD_ID, 1 } });

	// equipment
	add_recipe(C::STAFF_ID, { { C::AXE_ID, 1 } }, { { C::BRANCH_ID, 1 } }, {}, {}, { { C::STAFF_ID, 1 } });
	add_recipe(C::AXE_ID, {}, { { C::BRANCH_ID, 1 }, { C::STONE_ID, 1 }, { C::VINE_ID, 1 } }, {}, {}, { { C::AXE_ID, 1 } }); // maybe need a sharp stone?
	add_recipe(C::BOW_ID, {}, { { C::BRANCH_ID, 1 }, { C::VINE_ID, 1 } }, {}, {}, { { C::BOW_ID, 1 } });
	add_recipe(C::SWORD_ID, {}, { { C::STONE_ID, 2 }, { C::STICK_ID, 1 } }, {}, {}, { { C::SWORD_ID, 1 } });

	// minerals (note we're using the in-ground form of the mineral for the name of the recipe)
	add_recipe(C::IRON_ID, {}, {}, { { C::IRON_DEPOSIT_ID, 1 } }, {}, { { C::IRON_ID, 1 } });
	add_recipe(C::LIMESTONE_ID, {}, {}, { { C::LIMESTONE_DEPOSIT_ID, 1 } }, {}, { { C::LIMESTONE_ID, 1 } });

	// other
	add_recipe(C::FORGE_ID, {}, { { C::STONE_ID, 20 } }, {}, {}, { { C::FORGE_ID, 1 } }); // 20 stones to build a forge (which is immovable)
	add_recipe(C::BLOOMERY_ID, {}, { { C::STONE_ID, 30 } }, {}, {}, { { C::BLOOMERY_ID, 1 } }); // 30 stones to build a bloomery (which is immovable)
	add_recipe(C::CHEST_ID, { { C::AXE_ID, 1 } }, { { C::BOARD_ID, 5 } }, {}, {}, { { C::CHEST_ID, 1 } });
	add_recipe(C::TABLE_ID, { { C::AXE_ID, 1 } }, { { C::BOARD_ID, 1 }, { C::BRANCH_ID, 4 } }, {}, {}, { { C::TABLE_ID, 1 } }); // uses a board and four branches, needs an axe

}

// recipe population
void Recipes::add_recipe(const std::string & name,
	const std::map<std::string, int> & inv_n, const std::map<std::string, int> & inv_r,
	const std::map<std::string, int> & loc_n, const std::map<std::string, int> & loc_r, const std::map<std::string, int> & yields)
{
	/* arguments in order:
	recipe name
	map of item IDs that need to be in inventory
	map of item IDs that need to be in inventory, are removed
	map of item IDs that need to be in the room
	map of item IDs that need to be in the room, are removed
	map of item IDs to be yielded */

	this->recipes.insert(std::pair<std::string, Recipe>(name, Recipe(inv_n, inv_r, loc_n, loc_r, yields)));
}
