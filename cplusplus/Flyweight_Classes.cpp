/// @file
/// @brief
/// Implementation of the @ref DesignPatternExamples_cpp::Flyweight_Class "Flyweight_Class",
/// @ref DesignPatternExamples_cpp::BigResource "BigResource", and
/// @ref DesignPatternExamples_cpp::BigResourceManager "BigResourceManager"
/// classes used in the @ref flyweight_pattern "Flyweight pattern"

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

    /// <summary>
    /// Retrieve or set the context for this class instance.
    /// </summary>
    Flyweight_Context Flyweight_Class::Context()
    {
        return _context;
    }

    void Flyweight_Class::SetContext(Flyweight_Context context)
    {
        _context = context;
    }


    /// <summary>
    /// Retrieve the "image" width from underlying big resource.
    /// </summary>
    int Flyweight_Class::ImageWidth()
    {
        if (_resource != nullptr)
        {
            return _resource->ImageWidth();
        }
        return 0;
    }


    /// <summary>
    /// Retrieve the "image" height from underlying big resource.
    /// </summary>
    int Flyweight_Class::ImageHeight()
    {
        if (_resource != nullptr)
        {
            return _resource->ImageHeight();
        }
        return 0;
    }

    /// <summary>
    /// Render the image associated with this flyweight instance into the given
    /// display at the given position.
    /// </summary>
    /// <param name="display">A list of character arrays representing the display.</param>
    /// <param name="position_x">leftmost position within the display to place
    /// the upper left corner of the image,</param>
    /// <param name="position_y">topmost position within the display to place
    /// the upper left corner of the image.</param>
    /// <remarks>
    /// Note that although this class has access to the context, it really
    /// shouldn't so as to keep a loose coupling between the context and
    /// this class.  Therefore, the entity calling Render() will pass the
    /// position in as parameters even though that position is likely
    /// coming from the context.
    /// </remarks>
    void Flyweight_Class::Render(std::vector<std::vector<char>>& display, int position_x, int position_y)
    {
        if (_resource != nullptr)
        {
            // Let the big resource handle the rendering at the given position.
            _resource->Render(display, position_x, position_y);
        }
    }


    ///////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////


    void BigResource::Render(std::vector<std::vector<char>>& display, int position_x, int position_y)
    {
        size_t display_width = display[0].size();
        size_t display_height = display.size();
        int starting_position_x = position_x;
        int starting_position_y = position_y;

        // Size of image to render (can be smaller than actual image if image
        // lies partially of right or bottom of display).
        size_t image_render_width = _resource[0].length();
        size_t image_render_height = _resource.size();

        // Position into image to start rendering from (non-zero if
        // image is off the left or top edge of display).
        int starting_row_in_image = 0;
        int starting_col_in_image = 0;

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
