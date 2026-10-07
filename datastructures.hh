// Datastructures.hh

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>
#include <tuple>
#include <utility>
#include <limits>
#include <functional>
#include <source_location>

// Omat includet
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <cstddef>
#include <memory>
#include <forward_list>
#include <cmath>

// Types for IDs
using StopID = long int;
using RegionID = std::string;
using RouteID = std::string;
using Name = std::string;

// Return values for cases where required thing was not found
RouteID const NO_ROUTE = "!!NO_ROUTE!!";
StopID const NO_STOP = -1;
RegionID const NO_REGION = "!!NO_REGION!!";

// Return value for cases where integer values were not found
int const NO_VALUE = std::numeric_limits<int>::min();

// Return value for cases where name values were not found
Name const NO_NAME = "!!NO_NAME!!";

// Type for a coordinate (x, y)
struct Coord
{
    int x = NO_VALUE;
    int y = NO_VALUE;
};

// Example: Defining == and hash function for Coord so that it can be used
// as key for std::unordered_map/set, if needed
inline bool operator==(Coord c1, Coord c2) { return c1.x == c2.x && c1.y == c2.y; }
inline bool operator!=(Coord c1, Coord c2) { return !(c1==c2); } // Not strictly necessary

struct CoordHash
{
    std::size_t operator()(Coord xy) const
    {
        auto hasher = std::hash<int>();
        auto xhash = hasher(xy.x);
        auto yhash = hasher(xy.y);
        // Combine hash values (magic!)
        return xhash ^ (yhash + 0x9e3779b9 + (xhash << 6) + (xhash >> 2));
    }
};

// Example: Defining < for Coord so that it can be used
// as key for std::map/set
inline bool operator<(Coord c1, Coord c2)
{
    if (c1.y < c2.y) { return true; }
    else if (c2.y < c1.y) { return false; }
    else { return c1.x < c2.x; }
}

// Return value for cases where coordinates were not found
Coord const NO_COORD = {NO_VALUE, NO_VALUE};

// Type for a distance (in metres)
using Distance = int;

// Return value for cases where Distance is unknown
Distance const NO_DISTANCE = NO_VALUE;


// This exception class is there just so that the user interface can notify
// about operations which are not (yet) implemented
class NotImplemented : public std::exception
{
public:
    explicit NotImplemented(std::string const msg = "",
                            const std::source_location location = std::source_location::current())
        : msg_{}
    {
        std::string funcname = location.function_name();
        if (auto namestart = funcname.find_last_of(':'); namestart != std::string::npos)
        { funcname.erase(0, namestart+1); }
        if (auto nameend = funcname.find_first_of('('); nameend != std::string::npos)
        { funcname.erase(nameend, std::string::npos); }
        msg_ = (!msg.empty() ? msg+" in " : "")+funcname+"()";
    }
    virtual const char* what() const noexcept override
    {
        return msg_.c_str();
    }
private:
    std::string msg_;
};

// ---------------------------------------------------------------------------------------
// This is the class you are supposed to implement

class Datastructures
{
public:
    Datastructures();
    ~Datastructures();

    // Estimate of performance:
    // Short rationale for estimate:
    int stop_count();

    // Estimate of performance:
    // Short rationale for estimate:
    void clear_all();

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<StopID> all_stops();

    // Estimate of performance:
    // Short rationale for estimate:
    bool add_stop(StopID id, Name const& name, Coord xy);

    // Estimate of performance:
    // Short rationale for estimate:
    Name get_stop_name(StopID);

    // Estimate of performance:
    // Short rationale for estimate:
    Coord get_stop_coord(StopID id);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<StopID> stops_alphabetically();

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<StopID> stops_coord_order();

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<StopID> find_stops(Name const& name);

    // Estimate of performance:
    // Short rationale for estimate:
    bool change_stop_name(StopID id, Name const& newname);

    // Estimate of performance:
    // Short rationale for estimate:
    bool change_stop_coord(StopID id, Coord newcoord);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance:
    // Short rationale for estimate:
    bool add_region(RegionID id, Name const& name);

    // Estimate of performance:
    // Short rationale for estimate:
    Name get_region_name(RegionID id);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<RegionID> all_regions();

    // Estimate of performance:
    // Short rationale for estimate:
    bool add_stop_to_region(StopID id, RegionID parentid);

    // Estimate of performance:
    // Short rationale for estimate:
    bool add_subregion_to_region(RegionID id, RegionID parentid);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<RegionID> stop_regions(StopID id);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<StopID> stops_closest_to(StopID id);

    // Estimate of performance:
    // Short rationale for estimate:
    bool remove_stop(StopID id);

    // Estimate of performance:
    // Short rationale for estimate:
    std::pair<Coord, Coord> region_bounding_box(RegionID id);

    // Estimate of performance:
    // Short rationale for estimate:
    RegionID stops_common_region(StopID id1, StopID id2);

    // Estimate of performance:
    // Short rationale for estimate:
    bool add_route(RouteID id, std::vector<StopID> stops);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<RouteID> all_routes();

    // Estimate of performance:
    // Short rationale for estimate:
    bool remove_route(RouteID id);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<std::pair<RouteID, StopID>> routes_from(StopID stopid);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<StopID> route_stops(RouteID id);

    // Estimate of performance:
    // Short rationale for estimate:
    void clear_routes();

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<std::tuple<StopID, RouteID, Distance>> journey_any(StopID fromstop, StopID tostop);

//    // Non-compulsory operations

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<std::tuple<StopID, RouteID, Distance>> journey_least_stops(StopID fromstop, StopID tostop);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<std::tuple<StopID, RouteID, Distance>> journey_with_cycle(StopID fromstop);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<std::tuple<StopID, RouteID, Distance>> journey_shortest_distance(StopID fromstop, StopID tostop);

private:
    // Add stuff needed for your class implementation here
    // Explain below your rationale for choosing the data structures you use in
    // this class.

    // struct containing all info about stop
    struct Stop_ {
        StopID stopID_;
        RegionID regionID_ = NO_REGION;
        RouteID routeID_ = NO_ROUTE;
        Name name_;
        Coord coord_;
    };

    // unordered_map holds all the stops for easy access to all stops through StopID without indexing
    std::unordered_map<StopID, Stop_> Stops_;

    // struct containing all info about region
    struct Region_ {
        RegionID regionID_ = NO_REGION;
        Name name_;
        std::vector<StopID> stops_;
    };

    // unordered_map holds all the regions for easy access to all regions through RegionID without indexing
    std::unordered_map<RegionID, Region_> Regions_;

};

#endif // DATASTRUCTURES_HH
