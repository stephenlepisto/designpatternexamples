/// @file
/// @brief
/// Implementation of the @ref DesignPatternExamples_cpp::Flyweight_Class "Flyweight_Class",
/// @ref DesignPatternExamples_cpp::BigResource "BigResource", and
/// @ref DesignPatternExamples_cpp::BigResourceManager "BigResourceManager"
/// classes used in the @ref flyweight_pattern

#include "Flyweight_Classes.h"

namespace DesignPatternExamples_cpp
{

    ///////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////

    Flyweight_Class::Flyweight_Class(BigResource* resource, Flyweight_Context context)
    {
        _resource = resource;
        _context = context;
    }

    Flyweight_Class::~Flyweight_Class()
    {
    }

    Flyweight_Context Flyweight_Class::Context()
    {
        return _context;
    }

    void Flyweight_Class::SetContext(Flyweight_Context context)
    {
        _context = context;
    }


    int Flyweight_Class::ImageWidth()
    {
        if (_resource != nullptr)
        {
            return _context.ImageWidth;
        }
        return 0;
    }


    int Flyweight_Class::ImageHeight()
    {
        if (_resource != nullptr)
        {
            return _context.ImageHeight;
        }
        return 0;
    }

    void Flyweight_Class::Render(std::vector<std::vector<char>>& display, int offset_x, int image_width, int image_height, int position_x, int position_y)
    {
        if (_resource != nullptr)
        {
            // Let the big resource handle the rendering at the given position.
            _resource->Render(display, offset_x, image_width, image_height, position_x, position_y);
        }
    }


    ///////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////


    void BigResource::Render(std::vector<std::vector<char>>& display, int offset_x, int image_width, int image_height, int position_x, int position_y)
    {
        size_t display_width = display[0].size();
        size_t display_height = display.size();
        int starting_position_x = position_x;
        int starting_position_y = position_y;

        // Size of image to render (can be smaller than actual image if image
        // lies partially of right or bottom of display).
        size_t image_render_width = image_width;
        size_t image_render_height = image_height;

        // Position into image to start rendering from (non-zero if
        // image is off the left or top edge of display).
        int starting_row_in_image = 0;
        int starting_col_in_image = offset_x;

        // Clip the image to the display.
        if (starting_position_x < 0)
        {
            starting_col_in_image = -starting_position_x;
            image_render_width += starting_position_x;
            starting_position_x = 0;
        }
        else if (starting_position_x + image_render_width > display_width)
        {
            image_render_width = display_width - starting_position_x;
        }
        if (starting_position_y < 0)
        {
            starting_row_in_image = -starting_position_y;
            image_render_height += starting_position_y;
            starting_position_y = 0;
        }
        else if (starting_position_y + image_render_height > display_height)
        {
            image_render_height = display_height - starting_position_y;
        }

        // If the image is even partially visible, render it
        if (image_render_width > 0 && image_render_height > 0)
        {
            int current_display_row = starting_position_y;
            int current_image_row = starting_row_in_image;
            for (size_t row = 0; row < image_render_height; ++row)
            {
                for (size_t col = 0; col < image_render_width; ++col)
                {
                    display[current_display_row][starting_position_x + col] = _resource[current_image_row][starting_col_in_image + col];
                }
                current_display_row += 1;
                current_image_row += 1;
            }
        }
    }

    int BigResource::ResourceId()
    {
        return _resourceId;
    }

    int BigResource::ImageWidth()
    {
        if (_resource.size() > 0)
        {
            return static_cast<int>(_resource[0].size());
        }
        return 0;
    }

    int BigResource::ImageHeight()
    {
        return static_cast<int>(_resource.size());
    }

    Flyweight_Class::unique_ptr_t BigResource::CreateFlyweight(Flyweight_Context context)
    {
        return std::make_unique<Flyweight_Class>(this, context);
    }


    ///////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////

    
    BigResourceManager::BigResourceList BigResourceManager::_resources;

    int BigResourceManager::_nextResourceId = 1;


    int BigResourceManager::GetNextResourceId()
    {
        int nextId = _nextResourceId;
        ++_nextResourceId;
        return nextId;
    }

    BigResource* BigResourceManager::FindResource(int resourceId)
    {
        BigResource* foundResource = nullptr;
        
        for (BigResourceList::iterator resourceIter = std::begin(_resources);
            resourceIter != std::end(_resources);
            resourceIter++)
        {
            if ((*resourceIter)->ResourceId() == resourceId)
            {
                foundResource = (*resourceIter).get();
                break;
            }
        }

        return foundResource;
    }

    int BigResourceManager::AddResource(std::vector<std::string> rawResource)
    {
        int newResourceId = GetNextResourceId();
        _resources.push_back(std::make_unique<BigResource>(rawResource, newResourceId));

        return newResourceId;
    }

    Flyweight_Class::unique_ptr_t BigResourceManager::CreateFlyweight(int bigResourceId, Flyweight_Context context)
    {
        Flyweight_Class::unique_ptr_t flyweightClass;
        BigResource* bigResource = FindResource(bigResourceId);
        if (bigResource != nullptr)
        {
            flyweightClass = bigResource->CreateFlyweight(context);
        }
        return flyweightClass;
    }

} // end namespace
