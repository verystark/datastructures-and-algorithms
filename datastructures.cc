// Datastructures.cc

#include <cstdlib>
#include <cassert>
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

bool Datastructures::add_subregion_to_region(RegionID /*id*/, RegionID /*parentid*/)
{
    // replace with your implementation
    throw NotImplemented();
}

std::vector<RegionID> Datastructures::stop_regions(StopID /*id*/)
{
    // replace with your implementation
    throw NotImplemented();
}

std::vector<StopID> Datastructures::stops_closest_to(StopID /*id*/)
{
    // replace with your implementation
    throw NotImplemented();
}

bool Datastructures::remove_stop(StopID /*id*/)
{
    // replace with your implementation
    throw NotImplemented();
}

std::pair<Coord,Coord> Datastructures::region_bounding_box(RegionID /*id*/)
{
    // replace with your implementation
    throw NotImplemented();
}

RegionID Datastructures::stops_common_region(StopID /*id1*/, StopID /*id2*/)
{
    // replace with your implementation
    throw NotImplemented();
}


bool Datastructures::add_route(RouteID /*id*/, std::vector<StopID> /*stops*/)
{
    // replace with your implementation
    throw NotImplemented();
}

std::vector<RouteID> Datastructures::all_routes()
{
    // replace with your implementation
    throw NotImplemented();
}

bool Datastructures::remove_route(RouteID /*id*/)
{
    // replace with your implementation
    throw NotImplemented();
}

std::vector<std::pair<RouteID, StopID>> Datastructures::routes_from(StopID /*stopid*/)
{
    // replace with your implementation
    throw NotImplemented();
}

std::vector<StopID> Datastructures::route_stops(RouteID /*id*/)
{
    // replace with your implementation
    throw NotImplemented();
}

void Datastructures::clear_routes()
{
    // replace with your implementation
    throw NotImplemented();
}

std::vector<std::tuple<StopID, RouteID, Distance>> Datastructures::journey_any(StopID /*fromstop*/, StopID /*tostop*/)
{
    // replace with your implementation
    throw NotImplemented();

}

std::vector<std::tuple<StopID, RouteID, Distance>> Datastructures::journey_least_stops(StopID /*fromstop*/, StopID /*tostop*/)
{
    // replace with your implementation
    throw NotImplemented();
}

std::vector<std::tuple<StopID, RouteID, Distance>> Datastructures::journey_with_cycle(StopID /*fromstop*/)
{
    // replace with your implementation
    throw NotImplemented();
}

std::vector<std::tuple<StopID, RouteID, Distance>> Datastructures::journey_shortest_distance(StopID /*fromstop*/, StopID /*tostop*/)
{
    // replace with your implementation
    throw NotImplemented();
}


