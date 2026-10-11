// Datastructures.cc

#include <cstdlib>
#include <cassert>
#include <queue>
#include <utility>

#include "datastructures.hh"

#include <random>

#include <cmath>

std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = std::uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

    return static_cast<Type>(start+num);
}

// Modify the code below to implement the functionality of the class.
// Also remove comments from the parameter names when you implement
// an operation (Commenting out parameter name prevents compiler from
// warning about unused parameters on operations you haven't yet implemented.)

Datastructures::Datastructures()
{

}

Datastructures::~Datastructures()
{

}

// return number of all stops
int Datastructures::stop_count()
{
    return Stops_.size();
}

// clear all current data structures
void Datastructures::clear_all()
{
    return Stops_.clear();
}

// go through all stops and return vector consisting of stop IDs
std::vector<StopID> Datastructures::all_stops()
{
    std::vector<StopID> all_stops;
    all_stops.reserve(Stops_.size());

    for (auto stop = Stops_.begin(); stop != Stops_.end(); ++stop) {
        all_stops.push_back(stop->first);
    }
    return all_stops;
}

// add stop with given parameters
bool Datastructures::add_stop(StopID id, const Name& name, Coord xy)
{
    // add new stop, if stop ID not found in stops
    auto result = Stops_.try_emplace(id, Stop_{.stopID_ = id, .name_ = name,  .coord_ = xy});

    // return true if new stop added, return false if stop added
    return result.second;
}

// return stop name with given ID
Name Datastructures::get_stop_name(StopID id)
{
    auto it = Stops_.find(id);

    // if ID found in stops return stop name, else return NO_NAME
    if (it != Stops_.end()) {
        return it->second.name_;
    }
    return NO_NAME;
}

// return stop coordinates with give ID
Coord Datastructures::get_stop_coord(StopID id)
{
    auto it = Stops_.find(id);

    // if ID found in stops return stop name, else return NO_COORD
    if (it != Stops_.end()) {
        return it->second.coord_;
    }
    return NO_COORD;
}

// add struct into vector and sort them alphabetically by name
std::vector<StopID> Datastructures::stops_alphabetically()
{
    // make vector and pre-allocate memory for it
    std::vector<StopID> result;
    result.reserve(Stops_.size());

    // add all IDs to vector
    for (const auto& [id, stop] : Stops_) {
        result.push_back(id);
    }

    // sort vector with IDs based on alphabetical order of names
    std::sort(result.begin(), result.end(), [this](StopID a, StopID b) {
        return Stops_.at(a).name_ < Stops_.at(b).name_;
    });

    return result;
}

// sort vector of stop IDs by distance of stop
std::vector<StopID> Datastructures::stops_coord_order()
{
    // make vector and pre-allocate memory for it
    std::vector<StopID> result;
    result.reserve(Stops_.size());

    // add all IDs to vector
    for (const auto& [id, stop] : Stops_) {
        result.push_back(id);
    }

    // sort vector based on distance of stop
    std::sort(result.begin(), result.end(), [this](StopID a, StopID b) {
        const auto& coordA = Stops_.at(a).coord_;
        const auto& coordB = Stops_.at(b).coord_;

        auto distA = std::hypot(coordA.x, coordA.y);
        auto distB = std::hypot(coordB.x, coordB.y);

        // sort by smaller distance
        if (distA != distB) {
            return distA < distB;
        }

        // if distance is equal return sort by smaller y
        return coordA.y < coordB.y;
    });

    return result;
}

// return vector of stops with given name, return empty vector if no stops with given name exist
std::vector<StopID> Datastructures::find_stops(Name const& name)
{
    // make vector for stops
    std::vector<StopID> result;

    // go through stops and add to vector if same name
    for (const auto& [id, stop] : Stops_) {
        if (stop.name_ == name) {
            result.push_back(id);
        }
    }

    return result;
}

// search for stop with ID and change name if found
bool Datastructures::change_stop_name(StopID id, const Name& newname)
{
    auto it = Stops_.find(id);

    // change stop name if ID found and return true, else return false
    if (it != Stops_.end()) {
        it->second.name_ = newname;
        return true;
    }
    return false;
}

// search for stop with ID and change coordinates if found
bool Datastructures::change_stop_coord(StopID id, Coord newcoord)
{
    auto it = Stops_.find(id);

    // change stop coordinates if ID found and return true, else return false
    if (it != Stops_.end()) {
        it->second.coord_ = newcoord;
        return true;
    }
    return false;
}

// add region with given parameters
bool Datastructures::add_region(RegionID id, const Name& name)
{
    // add new region if ID not found in regions
    auto result = Regions_.try_emplace(id, Region_{.regionID_ = id, .name_ = name});

    // return true if new region added, else false
    return result.second;
}

// returns region name with given ID
Name Datastructures::get_region_name(RegionID id)
{
    auto it = Regions_.find(id);

    // if ID found in Regions_ return region name, else return NO_NAME
    if (it != Regions_.end()) {
        return it->second.name_;
    }
    return NO_NAME;
}

// return vector of all regions
std::vector<RegionID> Datastructures::all_regions()
{
    // create vector and pre-allocate memory
    std::vector<RegionID> all_regions;
    all_regions.reserve(Regions_.size());

    // add all region IDs to vector
    for (const auto& [id, region] : Regions_) {
        all_regions.push_back(id);
    }

    return all_regions;
}

// add stop to region
bool Datastructures::add_stop_to_region(StopID id, RegionID parentid)
{
    auto stop_it = Stops_.find(id);
    auto region_it = Regions_.find(parentid);

    // if stop and region don't exist or stop already has region return false
    if (stop_it == Stops_.end() || region_it == Regions_.end() || stop_it->second.regionID_!= NO_REGION) {
        return false;
    }

    // connect stop to region and region to stop
    stop_it->second.regionID_ = parentid;
    region_it->second.stops_.push_back(id);

    return true;
}

// add subregion to region
bool Datastructures::add_subregion_to_region(RegionID id, RegionID parentid)
{
    auto subregion_it = Regions_.find(id);
    auto parent_it = Regions_.find(parentid);

    // if regions don't exist or subregion already has a parent return false
    if (subregion_it == Regions_.end() || parent_it == Regions_.end() || subregion_it->second.parent_ != NO_REGION) {
        return false;
    }

    // connect subregion and parent
    subregion_it->second.parent_ = parentid;
    parent_it->second.subregions_.push_back(id);

    return true;
}

// return vector with all regions where stop belongs to
std::vector<RegionID> Datastructures::stop_regions(StopID id)
{
    auto stop_it = Stops_.find(id);

    // if ID has no stop return vector with NO_REGION
    if (stop_it == Stops_.end()) {
        return { NO_REGION };
    }

    std::vector<RegionID> result;
    RegionID current_region = stop_it->second.regionID_;

    // go through regions and add them to vector
    while (current_region != NO_REGION) {
        result.push_back(current_region);

        auto region_it = Regions_.find(current_region);
        if (region_it != Regions_.end()) {
            current_region = region_it->second.parent_;
        } else {
            break;
        }
    }

    return result;
}

// return vector of closes 5 stops to given stop
std::vector<StopID> Datastructures::stops_closest_to(StopID id)
{
    auto stop_it = Stops_.find(id);

    // if given stop doesn't exist return NO_STOP
    if (stop_it == Stops_.end()) {
        return { NO_STOP };
    }

    Coord ref_coord = stop_it->second.coord_;

    // make vector and pre-allocate memory for it
    std::vector<StopID> all_stops;
    all_stops.reserve(Stops_.size());

    // add all other stops to vector
    for (const auto& [other_id, stop] : Stops_) {
        if (other_id != id) {
           all_stops.push_back(other_id);
        }
    }

    // compute euclidean distance and return closer one
    auto comp = [this, ref_coord](StopID a, StopID b) {
        const auto& coordA = Stops_.at(a).coord_;
        const auto& coordB = Stops_.at(b).coord_;

        auto distA = std::hypot(ref_coord.x - coordA.x, ref_coord.y - coordA.y);
        auto distB = std::hypot(ref_coord.x - coordB.x, ref_coord.y - coordB.y);

        if (distA != distB) {
            return distA < distB;
        }

        return coordA.y < coordB.y;
    };

    size_t count = std::min<size_t>(5, all_stops.size());

    // sort stops by shortest distance to given stop
    std::partial_sort(all_stops.begin(), all_stops.begin() + count, all_stops.end(), comp);

    return std::vector<StopID>(all_stops.begin(), all_stops.begin() + count);
}

// remove stop with given ID from system
bool Datastructures::remove_stop(StopID id)
{
    auto stop_it = Stops_.find(id);

    // if stop doesn't exist return false
    if (stop_it == Stops_.end()) {
        return false;
    }

    RegionID stop_regionid = stop_it->second.regionID_;

    // erase stop from region
    if (stop_regionid != NO_REGION) {
        std::erase(Regions_.at(stop_regionid).stops_, id);
    }

    // erase stop from Stops_
    Stops_.erase(id);

    return true;
}

// helper function for getting all stops inside region and subregions
void Datastructures::get_region_coords(RegionID id, std::vector<Coord>& coords)
{
    auto region_it = Regions_.find(id);
    if (region_it == Regions_.end()) {
        return;
    }

    const auto& region = region_it->second;

    // add all stops in region to coords
    for (StopID stop_id : region.stops_) {
        auto stop_it = Stops_.find(stop_id);
        if (stop_it != Stops_.end()) {
            coords.push_back(stop_it->second.coord_);
        }
    }

    // go to subregions recursively and add their stops
    for (RegionID subregion_id : region.subregions_) {
        get_region_coords(subregion_id, coords);
    }
}

// return box that fits all stops in region and its subregions
std::pair<Coord,Coord> Datastructures::region_bounding_box(RegionID id)
{
    auto region_it = Regions_.find(id);
    if (region_it == Regions_.end()) {
        return { NO_COORD, NO_COORD };
    }

    std::vector<Coord> coords;

    // call hepler function
    get_region_coords(id, coords);

    // if no stops in region or its subregions return pair with NO_COORD
    if (coords.empty()) {
        return { NO_COORD, NO_COORD };
    }

    int minX = coords.at(0).x;
    int minY = coords.at(0).y;
    int maxX = coords.at(0).x;
    int maxY = coords.at(0).y;

    // find min and max X, Y coordinates
    for (const auto& coord : coords) {
        if (coord.x < minX) minX = coord.x;
        if (coord.y < minY) minY = coord.y;
        if (coord.x > maxX) maxX = coord.x;
        if (coord.y > maxY) maxY = coord.y;
    }

    return { Coord{minX, minY}, Coord{maxX, maxY} };
}

// return RegionID of "first" shared region of given stops
RegionID Datastructures::stops_common_region(StopID id1, StopID id2)
{
    // check if stops exist
    auto stop1_it = Stops_.find(id1);
    auto stop2_it = Stops_.find(id2);
    if (stop1_it == Stops_.end() || stop2_it == Stops_.end()) {
        return NO_REGION;
    }

    // get vector of all regions connected to id1
    auto stop1_regions = stop_regions(id1);

    // make unordered_set of all regions connected to id2
    auto stop2_vector = stop_regions(id2);
    std::unordered_set<RegionID> stop2_regions(std::make_move_iterator(stop2_vector.begin()),
                                               std::make_move_iterator(stop2_vector.end()));

    // find first shared region of stops
    for (const auto& region1 : stop1_regions) {
        if (stop2_regions.find(region1) != stop2_regions.end()) {
            return region1;
        }
    }
    return NO_REGION;
}

// add new route to system
bool Datastructures::add_route(RouteID id, std::vector<StopID> stops)
{
    // check that route doesn't yet exist
    if (Routes_.find(id) != Routes_.end()) {
        return false;
    }

    // check enough stops given
    if (stops.size() <= 1) {
        return false;
    }

    // check all stops exist
    for (const auto& stop : stops) {
        if (Stops_.find(stop) == Stops_.end()) {
            return false;
        }
    }

    // add route to stop
    for (const auto& stop : stops) {
        Stops_[stop].routes_.push_back(id);
    }

    // add route to routes container
    Routes_.emplace(id, std::move(stops));

    return true;
}

// return vector consisting of all routes
std::vector<RouteID> Datastructures::all_routes()
{
    // make empty vector for routes and pre-allocate memory
    std::vector<RouteID> all_routes;
    all_routes.reserve(Routes_.size());

    // add route IDs to vector
    for (const auto& [routeID, stops] : Routes_) {
        all_routes.push_back(routeID);
    }

    return all_routes;
}

// remove route and return true if found, else return false
bool Datastructures::remove_route(RouteID id)
{
    // check if route exists
    auto route_it = Routes_.find(id);
    if (route_it == Routes_.end()) {
        return false;
    }

    // remove route from stop containers
    for (const auto& stop : route_it->second) {
        auto stop_it = Stops_.find(stop);
        if (stop_it != Stops_.end()) {
            std::erase(stop_it->second.routes_, id);
        }
    }

    // remove route from Routes_ unordered_map
    Routes_.erase(route_it);
    return true;
}

// return vector of next stops from given stop
std::vector<std::pair<RouteID, StopID>> Datastructures::routes_from(StopID stopid)
{
    // check if given stop exists
    auto stop_it = Stops_.find(stopid);
    if (stop_it == Stops_.end()) {
        return {{NO_ROUTE, NO_STOP}};
    }

    std::vector<std::pair<RouteID, StopID>> routes_from;

    // go through all routes from stop and add next stop to vector
    const auto& stop_routes = stop_it->second.routes_;
    for (const auto& routeID : stop_routes) {
        auto route_it = Routes_.find(routeID);

        // if route has no stops do nothing
        if (route_it == Routes_.end()) {
            continue;
        }

        const auto& route_stops = route_it->second;

        auto it = std::find(route_stops.begin(), route_stops.end(), stopid);

        // add route and next stop to vector
        if (it != route_stops.end() && (it + 1) != route_stops.end()) {
            StopID next_stop = *(it + 1);
            routes_from.push_back({routeID, next_stop});
        }
    }

    return routes_from;
}

// return route stops in order
std::vector<StopID> Datastructures::route_stops(RouteID id)
{
    // check that route exists
    auto route_it = Routes_.find(id);
    if (route_it == Routes_.end()) {
        return {NO_STOP};
    }

    return route_it->second;
}

// delete all routes from system
void Datastructures::clear_routes()
{
    // clear routes from stops
    for (auto& [id, stop] : Stops_) {
        stop.routes_.clear();
    }

    Routes_.clear();
}

// return journey between given stops
std::vector<std::tuple<StopID, RouteID, Distance>> Datastructures::journey_any(StopID fromstop, StopID tostop)
{
    // check if stops exist
    auto fromstop_it = Stops_.find(fromstop);
    auto tostop_it = Stops_.find(tostop);
    if (fromstop_it == Stops_.end() || tostop_it == Stops_.end()) {
        return {{NO_STOP, NO_ROUTE, NO_DISTANCE}};
    }

    if (fromstop == tostop) {
        return {{fromstop, NO_ROUTE, 0}};
    }

    // create containers for BFS
    std::queue<StopID> queue;
    std::unordered_set<StopID> visited;
    std::unordered_map<StopID, std::pair<StopID, RouteID>> came_from;

    queue.push(fromstop);
    visited.insert(fromstop);

    bool found = false;

    // BFS algorithm for finding journey
    while (!queue.empty()) {
        StopID current = queue.front();
        queue.pop();

        if (current == tostop) {
            found = true;
            break;
        }

        // add branches
        auto next_connections = routes_from(current);
        for (const auto& [route_id, next_stop] : next_connections) {
            if (next_stop != NO_STOP && visited.find(next_stop) == visited.end()) {
                visited.insert(next_stop);
                came_from[next_stop] = {current, route_id};
                queue.push(next_stop);
            }
        }
    }

    if (!found) {
        return {};
    }

    std::vector<std::pair<StopID, RouteID>> path_reversed;
    StopID curr = tostop;

    // create path by going backwards the journey
    while (curr != fromstop) {
        auto [prev_stop, route_id] = came_from[curr];
        path_reversed.push_back({curr, route_id});
        curr = prev_stop;
    }
    path_reversed.push_back({fromstop, NO_ROUTE});

    // reverse path to correct order
    std::reverse(path_reversed.begin(), path_reversed.end());

    std::vector<std::tuple<StopID, RouteID, Distance>> result;
    result.reserve(path_reversed.size());

    Distance total_distance = 0;

    StopID prev_id = path_reversed.front().first;
    result.push_back({prev_id, NO_ROUTE, 0});

    // calculate distances of stops on path and add to result
    for (size_t i = 1; i < path_reversed.size(); ++i) {
        StopID curr_id = path_reversed.at(i).first;
        RouteID route_used = path_reversed.at(i).second;

        Coord coord1 = Stops_.find(prev_id)->second.coord_;
        Coord coord2 = Stops_.find(curr_id)->second.coord_;

        auto dist = static_cast<Distance>(std::hypot(coord1.x - coord2.x, coord1.y - coord2.y));

        total_distance += dist;
        result.push_back({curr_id, route_used, total_distance});

        prev_id = curr_id;
    }

    return result;
}

// return journey with least stops
std::vector<std::tuple<StopID, RouteID, Distance>> Datastructures::journey_least_stops(StopID fromstop, StopID tostop)
{
    // check if stops exist
    auto fromstop_it = Stops_.find(fromstop);
    auto tostop_it = Stops_.find(tostop);
    if (fromstop_it == Stops_.end() || tostop_it == Stops_.end()) {
        return {{NO_STOP, NO_ROUTE, NO_DISTANCE}};
    }

    if (fromstop == tostop) {
        return {{fromstop, NO_ROUTE, 0}};
    }

    // create containers for BFS
    std::queue<StopID> queue;
    std::unordered_set<StopID> visited;
    std::unordered_map<StopID, std::pair<StopID, RouteID>> came_from;

    queue.push(fromstop);
    visited.insert(fromstop);

    bool found = false;

    // BFS algorithm for finding journey
    while (!queue.empty()) {
        StopID current = queue.front();
        queue.pop();

        if (current == tostop) {
            found = true;
            break;
        }

        // add branches
        auto next_connections = routes_from(current);
        for (const auto& [route_id, next_stop] : next_connections) {
            if (next_stop != NO_STOP && visited.find(next_stop) == visited.end()) {
                visited.insert(next_stop);
                came_from[next_stop] = {current, route_id};
                queue.push(next_stop);
            }
        }
    }

    if (!found) {
        return {};
    }

    std::vector<std::pair<StopID, RouteID>> path_reversed;
    StopID curr = tostop;

    // create path
    while (curr != fromstop) {
        auto [prev_stop, route_id] = came_from[curr];
        path_reversed.push_back({curr, route_id});
        curr = prev_stop;
    }

    path_reversed.push_back({fromstop, NO_ROUTE});

    // reverse path to right order
    std::reverse(path_reversed.begin(), path_reversed.end());

    std::vector<std::tuple<StopID, RouteID, Distance>> result;
    result.reserve(path_reversed.size());

    Distance total_distance = 0;

    // calculate distance and add to result in correct form
    for (size_t i = 0; i < path_reversed.size(); ++i) {
        StopID curr_id = path_reversed.at(i).first;

        if (i > 0) {
            StopID prev_id = path_reversed.at(i - 1).first;

            Coord coord1 = Stops_.find(prev_id)->second.coord_;
            Coord coord2 = Stops_.find(curr_id)->second.coord_;

            total_distance += static_cast<Distance>(std::hypot(coord1.x - coord2.x, coord1.y - coord2.y));
        }

        RouteID route_to_next = (i + 1 < path_reversed.size()) ? path_reversed.at(i + 1).second : NO_ROUTE;

        result.push_back({curr_id, route_to_next, total_distance});
    }

    return result;
}

// DFS algorithm helper function
bool Datastructures::dfs_algo(StopID curr, std::vector<std::pair<StopID, RouteID>>& current_path, std::unordered_set<StopID>& visited, std::unordered_set<StopID>& in_stack)
{
    visited.insert(curr);
    in_stack.insert(curr);

    // look for cycle
    auto connections = routes_from(curr);
    for (const auto& [route_id, next_stop] : connections) {
        if (next_stop == NO_STOP) continue;

        // add route to path
        current_path.push_back({next_stop, route_id});

        // check if next stop already on path
        if (in_stack.find(next_stop) != in_stack.end()) {
            return true;
        }

        // if next stop not yet checked call dfs_algo recursively
        if (visited.find(next_stop) == visited.end()) {
            if (dfs_algo(next_stop, current_path, visited, in_stack)) {
                return true;
            }
        }

        current_path.pop_back();
    }

    in_stack.erase(curr);
    return false;
}

// return journey with cycle
std::vector<std::tuple<StopID, RouteID, Distance>> Datastructures::journey_with_cycle(StopID fromstop)
{

    // check that stops exists
    if (Stops_.find(fromstop) == Stops_.end()) {
        return {{NO_STOP, NO_ROUTE, NO_DISTANCE}};
    }

    std::vector<std::pair<StopID, RouteID>> current_path;
    std::unordered_set<StopID> visited;
    std::unordered_set<StopID> in_stack;

    current_path.push_back({fromstop, NO_ROUTE});

    // do DFS search
    bool cycle_found = dfs_algo(fromstop, current_path, visited, in_stack);

    // if no path with cycle found return empty vector
    if (!cycle_found) {
        return {};
    }

    std::vector<std::tuple<StopID, RouteID, Distance>> result;
    result.reserve(current_path.size());

    Distance total_distance = 0;

    // add path to result vector
    for (size_t i = 0; i < current_path.size(); ++i) {
        StopID curr_id = current_path.at(i).first;

        if (i > 0) {
            StopID prev_id = current_path.at(i - 1).first;
            Coord coord1 = Stops_.find(prev_id)->second.coord_;
            Coord coord2 = Stops_.find(curr_id)->second.coord_;
            total_distance += static_cast<Distance>(std::hypot(coord1.x - coord2.x, coord1.y - coord2.y));
        }

        RouteID route_to_next = (i + 1 < current_path.size()) ? current_path.at(i + 1).second : NO_ROUTE;

        result.push_back({curr_id, route_to_next, total_distance});
    }

    return result;
}

std::vector<std::tuple<StopID, RouteID, Distance>> Datastructures::journey_shortest_distance(StopID /*fromstop*/, StopID /*tostop*/)
{
    // replace with your implementation
    throw NotImplemented();
}


