#include <list>
#include <utility>
#include <ijengine/core/environment.h>
#include <ijengine/core/rect.h>
#include <map>

#include "map.h"


using namespace std;

Map::Map(int qnt_salas) : current_room(nullptr)
{	
	GenerateMap(qnt_salas);

}
// Room Criation
void Map::CreateRoom(Room *room, int *id,int x, int y, int qnt)
{
	int randomVar;
    int randomType = rand() % 3; 
    string type;
	
	randomVar = rand() % 100+1;

    if(randomVar <= 25)
    {
        randomVar = LEFT;
    }

    if(randomVar > 25 && randomVar <= 50)
    {
        randomVar = RIGHT;
    }

    if(randomVar > 50 && randomVar <= 75)
    {
        randomVar = TOP;
    }

    if(randomVar > 75 && randomVar <= 100)
    {
        randomVar = BOTTOM;
    }

    char sala[256];
    sprintf(sala, "sala %d", *id);

    if(randomType < 2)
        type = "None";
    else if (randomType < 3)
        type = "Cela";
    if(*id == (int)(qnt*0.5))
        type = "KeyRoom";
    if(*id == (int)(qnt*0.9))
        type = "Final";



    if(room->type == "Final")
    {
        *id-=1;
        return;
    }
    
	switch(randomVar)
	{	
		case LEFT:
			if(room->r_left != nullptr)
				CreateRoom(room->r_left, id, x-1, y, qnt);
			else if(x-1 >= 0 && matriz[x-1][y] == false && (room->room_type() != "Cela" || (room->room_type() == "Cela" && room->r_right)))
            {
                if(type == "Cela")
                    type += 'H';

            	room->Room::r_left = new Room(this, sala, type, nullptr, nullptr, room, nullptr);
                room_list.push_back(room->r_left);
                room->r_left->pos_x = x-1;
                room->r_left->pos_y = y;
                matriz[x-1][y] = true;
            }	
            else
            {
                *id-=1;
                return;
            }
			break;
			
		case RIGHT:
			if(room->r_right != nullptr)
				CreateRoom(room->r_right, id, x+1, y, qnt);
			else if(x+1 < qnt && matriz[x+1][y] == false && (room->room_type() != "Cela" || (room->room_type() == "Cela" && room->r_left)))
            {
                if(type == "Cela")
                    type += 'H';

            	room->r_right = new Room(this, sala, type, room, nullptr, nullptr, nullptr);
                room_list.push_back(room->r_right);
                room->r_right->pos_x = x+1;
                room->r_right->pos_y = y;
                matriz[x+1][y] = true;
            }
            else
            {   
                *id-=1;
                return;
            }
			break;
		
		case TOP:
			if(room->r_top != nullptr)
				CreateRoom(room->r_top, id, x, y-1, qnt);
			else if(y-1 >= 0 && matriz[x][y-1] == false && (room->room_type() != "Cela" || (room->room_type() == "Cela" && room->r_botton)))
            {
                if(type == "Cela")
                    type += 'V';
                
				room->r_top = new Room(this, sala, type, nullptr, nullptr, nullptr, room);
                room_list.push_back(room->r_top);
                room->r_top->pos_x = x;
                room->r_top->pos_y = y-1;
                matriz[x][y-1] = true;
            }
            else
            {   
                *id-=1;
                return;
            }
			break;
		
		case BOTTOM:
			if(room->r_botton != nullptr)
				CreateRoom(room->r_botton, id, x, y+1, qnt);
			else if(y+1 < qnt && matriz[x][y+1] == false && (room->room_type() != "Cela" || (room->room_type() == "Cela" && room->r_top)))
            {
                if(type == "Cela")
                    type += 'V';
                
				room->r_botton = new Room(this, sala, type, nullptr, room, nullptr, nullptr);
                room_list.push_back(room->r_botton);
                room->r_botton->pos_x = x;
                room->r_botton->pos_y = y+1;
                matriz[x][y+1] = true;
            }
            else
            {
                *id-=1;
                return;
            }
			break;
	}
}

// Generate all the map
void Map::GenerateMap(int quantidade_salas)
{
	
    int x = quantidade_salas/2;
    int y = quantidade_salas/2;
    int id = 1;

    matriz = (bool**) malloc(sizeof(bool*)*(quantidade_salas));

    for(int i = 0; i < quantidade_salas; i++)
    {
    	matriz[i] = (bool*) malloc(sizeof(bool)*(quantidade_salas));
        for(int j = 0; j < quantidade_salas; j++)
	        {
            matriz[i][j] = false;
        }
    }

	Room *room = new Room(this, "sala 0", "None", nullptr, nullptr, nullptr, nullptr);
    room_list.push_back(room);
    current_room = room;
    last_room = room;

	matriz[x][y] = true;

    Room * aux = room_list.at(rand() % id);
    aux->pos_x = x;
    aux->pos_y = y;

	for(int id = 1; id < quantidade_salas; id++)
	{	
        Room * aux = room_list.at(rand() % id);
		CreateRoom(aux, &id, aux->pos_x, aux->pos_y, quantidade_salas);
        aux ++;
	}
    for(int i=quantidade_salas-1; i>=0; i--)
    {
        free (matriz[i]);
    }
    free(matriz);
}
    
void
Map::remove_item(Object *item)
{
    current_room->remove_item(item);
}

Room *
Map::room()
{
	return current_room;
}

void
Map::set_current(Room *nova)
{
	current_room = nova;
}

void Map::draw_self()
{
    if (current_room)
        current_room->draw();
}

const list<Object *>&
Map::itens() 
{
    return current_room->get_items();
}

void
Map::update_self(unsigned long elapsed)
{
    current_room->update(elapsed);
}
