/// @file
/// @brief
/// Implementation of the @ref DesignPatternExamples_cpp::Visitor_Village "Visitor_Village" class.

#include "Visitor_Village.h"
#include "Visitor_Element_Classes.h"


namespace DesignPatternExamples_cpp
{

    void Visitor_Village::LoadVillage()
    {
        Name = "Village of Self-Sufficiency";

        {
            shops.push_back(std::make_unique<Visitor_Restaurant>());
            Visitor_Shop::unique_ptr_t& shop = shops.back();
            shop->SetName("Joe's Burger Joint");
            shop->SetAddress("47 Millings Rd.");
            shop->SetVillage(this);
            shop->SetIngredientsForItems(MapOfStrings{
                    { "hamburger", { "ground beef", "hamburger buns", "ketchup", "mustard", "mayonnaise", "lettuce", "tomato", "onion", "pickles" } }
                });
        }

        {
            shops.push_back(std::make_unique<Visitor_Butcher>());
            Visitor_Shop::unique_ptr_t& shop = shops.back();
            shop->SetName("Amelia's Butcher Shop");
            shop->SetAddress("12 Klaxon Ave.");
            shop->SetVillage(this);
            shop->SetIngredientsForItems(MapOfStrings{
                    {"ground beef", { } }
                });
        }

        {
            shops.push_back(std::make_unique<Visitor_Baker>());
            Visitor_Shop::unique_ptr_t& shop = shops.back();
            shop->SetName("Oxel's Breads and Buns Bakery");
            shop->SetAddress("131 Worthington Dr.");
            shop->SetVillage(this);
            shop->SetIngredientsForItems(MapOfStrings{
                    {"hamburger buns", { } }
                });
        }

        {
            shops.push_back(std::make_unique<Visitor_CondimentGrocer>());
            Visitor_Shop::unique_ptr_t& shop = shops.back();
            shop->SetName("Connie's Condiments");
            shop->SetAddress("83 Millings Rd.");
            shop->SetVillage(this);
            shop->SetIngredientsForItems(MapOfStrings{
                    { "ketchup", { "fresh ketchup" } },
                    { "mustard", { "fresh mustard" } },
                    { "mayonnaise", { "fresh mayonnaise" } }
                });
        }

        {
            shops.push_back(std::make_unique<Visitor_VegetableGrocer>());
            Visitor_Shop::unique_ptr_t& shop = shops.back();
            shop->SetName("Florence's Vegetables");
            shop->SetAddress("32 Main St.");
            shop->SetVillage(this);
            shop->SetIngredientsForItems(MapOfStrings{
                    { "lettuce", { } },
                    { "tomato", { } },
                    { "onion", { } },
                    { "cucumber", { } },
                    { "mustard seed", { } }
                });
        }

        {
            shops.push_back(std::make_unique<Visitor_PickleGrocer>());
            Visitor_Shop::unique_ptr_t& shop = shops.back();
            shop->SetName("Larry's Pickle Emporium");
            shop->SetAddress("34 Main St.");
            shop->SetVillage(this);
            shop->SetIngredientsForItems(MapOfStrings{
                    {"pickles", { "vinegar", "cucumber", "salt" } }
                });
        }

        {
            shops.push_back(std::make_unique<Visitor_Maker>());
            Visitor_Shop::unique_ptr_t& shop = shops.back();
            shop->SetName("Klyde and Sons Ketchup Makers");
            shop->SetAddress("800 Overtown Rd.");
            shop->SetVillage(this);
            shop->SetIngredientsForItems(MapOfStrings{
                    {"fresh ketchup", { } }
                });
        }

        {
            shops.push_back(std::make_unique<Visitor_Maker>());
            Visitor_Shop::unique_ptr_t& shop = shops.back();
            shop->SetName("Molly's Mustard Mart");
            shop->SetAddress("810 Overtown Rd.");
            shop->SetVillage(this);
            shop->SetIngredientsForItems(MapOfStrings{
                    {"fresh mustard", { "vinegar", "mustard seed" } }
                });
        }

        {
            shops.push_back(std::make_unique<Visitor_Maker>());
            Visitor_Shop::unique_ptr_t& shop = shops.back();
            shop->SetName("Turk's Mayo Supply");
            shop->SetAddress("820 Overtown Rd.");
            shop->SetVillage(this);
            shop->SetIngredientsForItems(MapOfStrings{
                    {"fresh mayonnaise", { } }
                });
        }

        {
            shops.push_back(std::make_unique<Visitor_Maker>());
            Visitor_Shop::unique_ptr_t& shop = shops.back();
            shop->SetName("Vinnies' Sour Flavors");
            shop->SetAddress("830 Overtown Rd.");
            shop->SetVillage(this);
            shop->SetIngredientsForItems(MapOfStrings{
                    { "vinegar", { } }
                });
        }

        {
            shops.push_back(std::make_unique<Visitor_Maker>());
            Visitor_Shop::unique_ptr_t& shop = shops.back();
            shop->SetName("Jessie's Salt Works");
            shop->SetAddress("920 Overtown Rd.");
            shop->SetVillage(this);
            shop->SetIngredientsForItems(MapOfStrings{
                    {"salt", { } }
                });
        }
    }


    void Visitor_Village::Accept(Visitor* visitor)
    {
        for(auto& shop : shops)
        {
            shop->Accept(visitor);
        }
    }

} // end namespace
