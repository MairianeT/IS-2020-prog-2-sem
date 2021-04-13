#include <fstream>
#include "pugixml.hpp"
#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <math.h>
#pragma execution_character_set("utf-8")

double km_in_degree_x = 40088.55 / 360; 
double km_in_degree_y = 20088 / 360; 

void PrintSet(const std::set<std::string>& s) {
    for (auto el : s) {
        std::cout << el << std::endl;
    }
}



struct station {
    std::string name;
    std::string type_of_vehicle;
    double x, y;
    std::vector <std::string> streets;
    std::vector <std::string> routes;
};

void PrindStations(const std::vector<station>& s) {
    for (int i = 0; i < s.size(); i++) {
        std::cout << s[i].name << std::endl << s[i].type_of_vehicle << std::endl;
        for (int j = 0; j < s[i].routes.size(); j++)
            std::cout << s[i].routes[j] << " ";

        std::cout << std::endl;
        for (int j = 0; j < s[i].streets.size(); j++)
            std::cout << s[i].streets[j] << " ";
        std::cout << std::endl << s[i].x << " " << s[i].y << std::endl << std::endl;
    }
}

void MaxStations(const std::vector<station>& st) {
    std::multiset<std::string> routes_list;
    for (auto s : st) {
        for (auto r : s.routes) {
            routes_list.insert(r);
        }
    }
    int max = 0;
    std::string max_route;
    std::vector<std::string> routes_list_str;
    std::multiset<std::string> ::iterator iter = routes_list.begin();
    for (; iter != routes_list.end(); iter++) {
        routes_list_str.push_back(*iter);
    }

    for (int i = 0; i < routes_list_str.size(); i++) {
        if (max < routes_list.count(routes_list_str[i])) {
            max = routes_list.count(routes_list_str[i]);
            max_route = routes_list_str[i];
        }
    }
    std::cout << "— маршрут " << max_route << ", " << max << " остановок" << std::endl;
}
void MaxStreet(const std::vector<station>& st) {
    std::multiset<std::string> street_list;
    for (auto s : st) {
        for (auto r : s.streets) {
            street_list.insert(r);
        }
    }
    int max = 0;
    std::string max_street;
    std::vector<std::string> street_list_str;
    std::multiset<std::string> ::iterator iter = street_list.begin();
    for (; iter != street_list.end(); iter++) {
        street_list_str.push_back(*iter);
    }

    for (int i = 0; i < street_list_str.size(); i++) {
        if (max < street_list.count(street_list_str[i]) && street_list_str[i].length() > 1) {
            max = street_list.count(street_list_str[i]);
            max_street = street_list_str[i];
        }
    }
    std::cout << "— " << max_street << ", " << max << " остановок" << std::endl;
}

void Distance(const std::vector<station>& st){
    std::set<std::string> routes_list;
    for (auto s : st) {
        for (auto r : s.routes) {
            routes_list.insert(r);
        }
    }
    std::string max_route;
    std::vector<std::string> routes_list_str;
    std::set<std::string> :: iterator iter = routes_list.begin();
    for (; iter != routes_list.end(); iter++) {
        routes_list_str.push_back(*iter);
    }
    
    double x0 = 0, y0;
    std::vector<double> dist(routes_list_str.size(), 0);

    for (int i = 0; i < routes_list_str.size(); i++) {
        for (auto s : st) {
            for (auto cur : s.routes){
                if (cur == routes_list_str[i]) {
                    if (x0 == 0){
                        x0 = s.x;
                        y0 = s.y;
                    }
                    else {
                            dist[i] += sqrt(pow(km_in_degree_x*(s.x - x0), 2) + pow(km_in_degree_y*(s.y - y0), 2));
                            x0 = s.x;
                            y0 = s.y;
                    }
                }
            }
        }
        x0 = 0; 
        y0 = 0;

    }
    int max_i = 0;
    for (int i = 0; i < dist.size(); i++) {
        if (dist[max_i] < dist[i]) {
            max_i = i;
        }
    }
    std::cout << " маршрут: " << routes_list_str[max_i] << ", расстояние: " << dist[max_i] << "км" << std::endl;

}

int main() {


    system("chcp 65001");

    pugi::xml_document doc;
    std::ifstream stream("transport.xml");
    pugi::xml_parse_result result = doc.load(stream);
    pugi::xml_node data = doc.child("dataset").child("transport_station");

    std::vector <station> stations;
    std::vector <station> buses_stations;
    std::vector <station> trolleybuses_stations;
    std::vector <station> trams_stations;
    std::set<std::string> vehicle;
    std::string str;

    while (data) {
        std::string coor = data.child_value("coordinates");
        double x = atof(coor.substr(0, 9).c_str());
        double y = atof(coor.substr(10, 9).c_str());

        std::vector <std::string> streets;
        std::string location = data.child_value("location");

        str.clear();
        int f = 0;
        for (char c : location) {
            if (f == 1) f = 0; else
                if (c == ',') {
                    streets.push_back(str);
                    str.clear();
                    f = 1;
                }
                else {
                    str.append(1, c);
                }
        }
        streets.push_back(str);

        std::vector <std::string> routes;
        std::string data_routes = data.child_value("routes");
        str.clear();
        for (char c : data_routes) {
            if (c == ',' || c == '.') {
                routes.push_back(str);
                str.clear();
            }
            else str.append(1, c);
        }
        routes.push_back(str);

        station cur_station = {
            data.child_value("the_official_name"),
            data.child_value("type_of_vehicle"),
            x,
            y,
            streets,
            routes
        };
        stations.push_back(cur_station);

        if (cur_station.type_of_vehicle == "Автобус") {
            buses_stations.push_back(cur_station);
        }
        else {
            if (cur_station.type_of_vehicle == "Трамвай") trams_stations.push_back(cur_station);
            else trolleybuses_stations.push_back(cur_station);
        }
        data = data.next_sibling();

    }


    std::cout << "Маршрут с наибольшим количеством остановок:" << std::endl << "Автобус ";
    MaxStations(buses_stations);
    std::cout << "Троллейбус ";
    MaxStations(trolleybuses_stations);
    std::cout << "Трамвай ";
    MaxStations(trams_stations);

    std::cout << std::endl;

    std::cout << "Наиболее длинный маршрут:" << std::endl << "Автобус —";
    Distance(buses_stations);
    std::cout << "Троллейбус —";
    Distance(trolleybuses_stations);
    std::cout << "Трамвай —";
    Distance(trams_stations);

    std::cout << std::endl;

    std::cout << "Улица с наибольшим количеством остановок:" << std::endl;
    MaxStreet(stations);



    //PrintSet(routes_list);
    //PrindStations(buses_stations);

  
    return 0;
}
