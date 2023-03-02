#pragma once
#ifndef __VISITOR_VILLAGE_H__
#define __VISITOR_VILLAGE_H__

#include <memory>
#include <string>
#include <vector>

#include "Visitor_Shop.h"

namespace DesignPatternExamples_cpp
{
    /// <summary>
    /// Represents a collection of shops that can be visited.
    /// 
    /// This class works as the container of all objects that can be visited.
    /// All visits start in this container.
    /// </summary>
    class Visitor_Village
    {
    private:
        /// <summary>
        /// List of shops in this village.
        /// </summary>
        std::vector<Visitor_Shop::unique_ptr_t> shops;

    public:
        /// <summary>
        /// Name of this village
        /// </summary>
        std::string Name;

        /// <summary>
        /// Load the village.
        /// </summary>
        void LoadVillage();

        void Accept(Visitor* visitor);

    };

} // end namespace

#endif // __VISITOR_VILLAGE_H__

