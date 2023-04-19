#include <sqlite_modern_cpp.h>

#include <iostream>

void input(int &map_id, int &race_id, int &time_score);
void data_registration(int map_id, int race_id, int time_score);
void show_record(int map_id);

int main(int, char**) 
{
    try 
    {
        int map_id;
        int race_id;
        int time_score;

        input(map_id, race_id, time_score);
        data_registration(map_id, race_id, time_score);
        input(map_id, race_id, time_score);
        data_registration(map_id, race_id, time_score);
        input(map_id, race_id, time_score);
        data_registration(map_id, race_id, time_score);

        std::cout << "Which map id: ";
        std::cin >> map_id;

        show_record(map_id);
    }
    catch (std::exception& e) 
    {
      std::cout << e.what() << "\n";
    }
}

void input(int &map_id, int &race_id, int &time_score)
{
    std::cout << "Input map id: ";
    std::cin >> map_id;
    std::cout << "Input race id: ";
    std::cin >> race_id;
    std::cout << "Input time score: ";
    std::cin >> time_score;
}

void data_registration(int map_id, int race_id, int time_score)
{
    sqlite::database db("table_records.db");

    db << "create table if not exists records ("
          "   _id integer primary key autoincrement not null,"
          "   map_id int,"
          "   race_id int,"
          "   time_score int"
          ");";

    db << "insert into records (map_id, race_id, time_score) values (?, ?, ?);" << map_id << race_id << time_score;
}

void show_record(int map_id)
{
    sqlite::database db("table_records.db");

    int best_time_score;
    (db << "select max(time_score) from records where map_id = ?" << map_id) >> best_time_score;
    std::cout << "The best result for map " << map_id << " is: " << best_time_score << "\n";
}