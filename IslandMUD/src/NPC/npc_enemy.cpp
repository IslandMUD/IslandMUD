/* Jim Viebke
Jun 3 2015 */

#include "npc_enemy.h"

Hostile_NPC::Hostile_NPC(const std::string & name, std::unique_ptr<World> & world) : Non_Player_Character(name, C::NPC_HOSTILE_FACTION_ID, world) {}

std::string Hostile_NPC::get_new_hostile_id(const std::unique_ptr<World> & world, const std::map<std::string, std::shared_ptr<Character>> & actors) const
{
	std::vector<std::string> hostile_ids;

	// extract location coordinates
	const int x = location.get_x(), y = location.get_y();

	// for each visible room
	for (int cx = x - (int)C::VIEW_DISTANCE; cx <= x + (int)C::VIEW_DISTANCE; ++cx)
	{
		for (int cy = y - (int)C::VIEW_DISTANCE; cy <= y + (int)C::VIEW_DISTANCE; ++cy)
		{
			Coordinate current(cx, cy);

			// skip over rooms that are out of bounds
			if (!current.is_valid()) continue;

			// for each actor in the room
			for (const std::string & actor_ID : world->room_at(current)->get_actor_ids())
			{
				// if the actor is a player character
				if (U::is<PC>(actors.find(actor_ID)->second))
				{
					// save the player character's ID
					hostile_ids.push_back(actor_ID);
				}
			}
		}
	}

	// no players are visible, no target was found
	if (hostile_ids.size() == 0) { return ""; }

	// at least one player character is in range

	// pick a random player character, return their ID
	return U::random_element_from(hostile_ids);
}
