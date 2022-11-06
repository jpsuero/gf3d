#include <string.h>

#include "simple_logger.h"
#include "simple_json.h"

#include "gf3d_config.h"

extern int __DEBUG;


VkPipelineBindPoint gf3d_config_pipeline_bindpoint_from_str(const char *str)
{
    if (!str)return 0;
    if (strcmp(str,"VK_PIPELINE_BIND_POINT_GRAPHICS")==0)
    {
        return VK_PIPELINE_BIND_POINT_GRAPHICS;
    }
    if (strcmp(str,"VK_PIPELINE_BIND_POINT_COMPUTE")==0)
    {
        return VK_PIPELINE_BIND_POINT_COMPUTE;
    }
    //NOTE: there are a lot more, but depend on extensions
    return 0;
}


VkDependencyFlags gf3d_config_dependency_flag_bits_from_str(const char *str)
{
    if (!str)return 0;
    if (strcmp(str,"VK_DEPENDENCY_BY_REGION_BIT")==0)
    {
        return VK_DEPENDENCY_BY_REGION_BIT;
    }
    if (strcmp(str,"VK_DEPENDENCY_DEVICE_GROUP_BIT")==0)
    {
        return VK_DEPENDENCY_DEVICE_GROUP_BIT;
    }
    if (strcmp(str,"VK_DEPENDENCY_VIEW_LOCAL_BIT")==0)
    {
        return VK_DEPENDENCY_VIEW_LOCAL_BIT;
    }
    return 0;
}

VkDependencyFlags gf3d_config_dependency_flag_bits(SJson *array)
{
    SJson *item;
    int i,c;
    const char *str;
    VkDependencyFlags flags = 0;
    
    if (!array)return 0;
    c = sj_array_get_count(array);
    for (i = 0; i < c; i++)
    {
        item = sj_array_get_nth(array,i);
        if (!item)continue;
        str = sj_get_string_value(item);
        if (!str)continue;
        flags |= gf3d_config_dependency_flag_bits_from_str(str);
    }
    return flags;
}

VkAccessFlagBits gf3d_config_access_flag_bits_from_str(const char *str)
{
    if (!str)return 0;
    if (strcmp(str,"VK_ACCESS_INDIRECT_COMMAND_READ_BIT")==0)
    {
        return VK_ACCESS_INDIRECT_COMMAND_READ_BIT;
    }
    if (strcmp(str,"VK_ACCESS_INDEX_READ_BIT")==0)
    {
        return VK_ACCESS_INDEX_READ_BIT;
    }
    if (strcmp(str,"VK_ACCESS_VERTEX_ATTRIBUTE_READ_BIT")==0)
    {
        return VK_ACCESS_VERTEX_ATTRIBUTE_READ_BIT;
    }
    if (strcmp(str,"VK_ACCESS_UNIFORM_READ_BIT")==0)
    {
        return VK_ACCESS_UNIFORM_READ_BIT;
    }
    if (strcmp(str,"VK_ACCESS_INPUT_ATTACHMENT_READ_BIT")==0)
    {
        return VK_ACCESS_INPUT_ATTACHMENT_READ_BIT;
    }
    if (strcmp(str,"VK_ACCESS_SHADER_READ_BIT")==0)
    {
        return VK_ACCESS_SHADER_READ_BIT;
    }
    if (strcmp(str,"VK_ACCESS_SHADER_WRITE_BIT")==0)
    {
        return VK_ACCESS_SHADER_WRITE_BIT;
    }
    if (strcmp(str,"VK_ACCESS_COLOR_ATTACHMENT_READ_BIT")==0)
    {
        return VK_ACCESS_COLOR_ATTACHMENT_READ_BIT;
    }
    if (strcmp(str,"VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT")==0)
    {
        return VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    }
    if (strcmp(str,"VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT")==0)
    {
        return VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT;
    }
    if (strcmp(str,"VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT")==0)
    {
        return VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
    }
    if (strcmp(str,"VK_ACCESS_TRANSFER_READ_BIT")==0)
    {
        return VK_ACCESS_TRANSFER_READ_BIT;
    }
    if (strcmp(str,"VK_ACCESS_TRANSFER_WRITE_BIT")==0)
    {
        return VK_ACCESS_TRANSFER_WRITE_BIT;
    }
    if (strcmp(str,"VK_ACCESS_HOST_READ_BIT")==0)
    {
        return VK_ACCESS_HOST_READ_BIT;
    }
    if (strcmp(str,"VK_ACCESS_HOST_WRITE_BIT")==0)
    {
        return VK_ACCESS_HOST_WRITE_BIT;
    }
    if (strcmp(str,"VK_ACCESS_MEMORY_READ_BIT")==0)
    {
        return VK_ACCESS_MEMORY_READ_BIT;
    }
    if (strcmp(str,"VK_ACCESS_MEMORY_WRITE_BIT")==0)
    {
        return VK_ACCESS_MEMORY_WRITE_BIT;
    }
    return 0;
}

VkAccessFlagBits gf3d_config_access_flag_bits(SJson *array)
{
    SJson *item;
    int i,c;
    const char *str;
    VkAccessFlagBits flags = 0;
    
    if (!array)return 0;
    c = sj_array_get_count(array);
    for (i = 0; i < c; i++)
    {
        item = sj_array_get_nth(array,i);
        if (!item)continue;
        str = sj_get_string_value(item);
        if (!str)continue;
        flags |= gf3d_config_access_flag_bits_from_str(str);
    }
    return flags;
}

VkSubpassDependency gf3d_config_subpass_dependency(SJson *config)
{
    SJson *array;
    const char *str;
    VkSubpassDependency dependency = {0};
    if (!config)return dependency;
    
    dependency.srcSubpass = VK_SUBPASS_EXTERNAL;//NOTE: this will need to be revisited as, it is not simple
    dependency.dstSubpass = 0;

    array = sj_object_get_value(config,"srcStageMask");
    if (array)
    {
        str = sj_get_string_value(array);
        dependency.srcStageMask = gf3d_config_pipeline_stage_flags_from_str(str);
    }
    array = sj_object_get_value(config,"dstStageMask");
    if (array)
    {
        str = sj_get_string_value(array);
        dependency.dstStageMask = gf3d_config_pipeline_stage_flags_from_str(str);
    }
    array = sj_object_get_value(config,"srcAccessMask");
    if (array)
    {
        dependency.srcAccessMask = gf3d_config_access_flag_bits(array);
    }
    array = sj_object_get_value(config,"dstAccessMask");
    if (array)
    {
        dependency.dstAccessMask = gf3d_config_access_flag_bits(array);
    }
    array = sj_object_get_value(config,"dependencyFlags");
    if (array)
    {
        dependency.dependencyFlags = gf3d_config_dependency_flag_bits(array);
    }
    return dependency;
}

VkPipelineStageFlags gf3d_config_pipeline_stage_flags(SJson *array)
{
    SJson *item;
    int i,c;
    const char *str;
    VkPipelineStageFlags flags = 0;
    
    if (!array)return 0;
    c = sj_array_get_count(array);
    for (i = 0; i < c; i++)
    {
        item = sj_array_get_nth(array,i);
        if (!item)continue;
        str = sj_get_string_value(item);
        if (!str)continue;
        flags |= gf3d_config_pipeline_stage_flags_from_str(str);
    }
    return flags;
}

VkPipelineStageFlags gf3d_config_pipeline_stage_flags_from_str(const char *str)
{    
    if (!str)return 0;
    if (strcmp(str,"VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT")==0)
    {
        return VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
    }
    if (strcmp(str,"VK_PIPELINE_STAGE_DRAW_INDIRECT_BIT")==0)
    {
        return VK_PIPELINE_STAGE_DRAW_INDIRECT_BIT;
    }
    if (strcmp(str,"VK_PIPELINE_STAGE_VERTEX_INPUT_BIT")==0)
    {
        return VK_PIPELINE_STAGE_VERTEX_INPUT_BIT;
    }
    if (strcmp(str,"VK_PIPELINE_STAGE_VERTEX_SHADER_BIT")==0)
    {
        return VK_PIPELINE_STAGE_VERTEX_SHADER_BIT;
    }
    if (strcmp(str,"VK_PIPELINE_STAGE_TESSELLATION_CONTROL_SHADER_BIT")==0)
    {
        return VK_PIPELINE_STAGE_TESSELLATION_CONTROL_SHADER_BIT;
    }
    if (strcmp(str,"VK_PIPELINE_STAGE_TESSELLATION_EVALUATION_SHADER_BIT")==0)
    {
        return VK_PIPELINE_STAGE_TESSELLATION_EVALUATION_SHADER_BIT;
    }
    if (strcmp(str,"VK_PIPELINE_STAGE_GEOMETRY_SHADER_BIT")==0)
    {
        return VK_PIPELINE_STAGE_GEOMETRY_SHADER_BIT;
    }
    if (strcmp(str,"VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT")==0)
    {
        return VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
    }
    if (strcmp(str,"VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT")==0)
    {
        return VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
    }
    if (strcmp(str,"VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT")==0)
    {
        return VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT;
    }
    if (strcmp(str,"VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT")==0)
    {
        return VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    }
    if (strcmp(str,"VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT")==0)
    {
        return VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT;
    }
    if (strcmp(str,"VK_PIPELINE_STAGE_TRANSFER_BIT")==0)
    {
        return VK_PIPELINE_STAGE_TRANSFER_BIT;
    }
    if (strcmp(str,"VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT")==0)
    {
        return VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
    }
    if (strcmp(str,"VK_PIPELINE_STAGE_HOST_BIT")==0)
    {
        return VK_PIPELINE_STAGE_HOST_BIT;
    }
    if (strcmp(str,"VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT")==0)
    {
        return VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT;
    }
    if (strcmp(str,"VK_PIPELINE_STAGE_ALL_COMMANDS_BIT")==0)
    {
        return VK_PIPELINE_STAGE_ALL_COMMANDS_BIT;
    }
    //NOTE: this does not include any 1.3 stage options or extension options
    return 0;
}

VkImageLayout gf3d_config_image_layer(SJson *config)
{
    const char *str;
    if (!config)return VK_IMAGE_LAYOUT_UNDEFINED;
    str = sj_get_string_value(config);
    if (!str)return VK_IMAGE_LAYOUT_UNDEFINED;
    return gf3d_config_image_layer_from_str(str);
}

VkImageLayout gf3d_config_image_layer_from_str(const char *str)
{
    if (!str)return VK_IMAGE_LAYOUT_UNDEFINED;
    if (strcmp(str,"VK_IMAGE_LAYOUT_UNDEFINED")==0)
    {
        return VK_IMAGE_LAYOUT_UNDEFINED;
    }
    else if (strcmp(str,"VK_IMAGE_LAYOUT_GENERAL")==0)
    {
        return VK_IMAGE_LAYOUT_GENERAL;
    }
    else if (strcmp(str,"VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL")==0)
    {
        return VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    }
    else if (strcmp(str,"VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL")==0)
    {
        return VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
    }
    else if (strcmp(str,"VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL")==0)
    {
        return VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;
    }
    else if (strcmp(str,"VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL")==0)
    {
        return VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    }
    else if (strcmp(str,"VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL")==0)
    {
        return VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
    }
    else if (strcmp(str,"VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL")==0)
    {
        return VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    }
    else if (strcmp(str,"VK_IMAGE_LAYOUT_PREINITIALIZED")==0)
    {
        return VK_IMAGE_LAYOUT_PREINITIALIZED;
    }
    //NOTE: there are a lot more of these, but are specific to later versions or extensions.  If you want to support more, just
    // add another else if set for what you want to support.
    return VK_IMAGE_LAYOUT_UNDEFINED;
}

VkAttachmentDescription gf3d_config_attachment_description(SJson *config,VkFormat format)
{
    int i,c;
    SJson *array,*item;
    const char *str;
    VkAttachmentDescription data = {0};//keeping it generic here for ease of copy/paste
    if (!config)
    {
        slog("no json provided for gf3d_config_attachment_description");
        return data;
    }

    array = sj_object_get_value(config,"flags");
    if (array)
    {
        c = sj_array_get_count(array);
        for (i = 0;i < c; i++)
        {
            item = sj_array_get_nth(array,i);
            if (!item)continue;
            str = sj_get_string_value(item);
            if (!str)continue;
            if (strcmp(str,"VK_ATTACHMENT_DESCRIPTION_MAY_ALIAS_BIT")==0)
            {
                //NOTE currently this is the only bit option in the API, but there may be more in the future
                data.flags |= VK_ATTACHMENT_DESCRIPTION_MAY_ALIAS_BIT;
            }
        }
        if (__DEBUG)slog("VkAttachmentDescription flags: %i",data.flags);
    }
    data.format = format;
    /*samples*/
    str = sj_object_get_value_as_string(config,"samples");
    if (str)
    {
        if (strcmp(str,"VK_SAMPLE_COUNT_1_BIT")==0)
        {
            data.samples = VK_SAMPLE_COUNT_1_BIT;
        }
        else if (strcmp(str,"VK_SAMPLE_COUNT_2_BIT")==0)
        {
            data.samples = VK_SAMPLE_COUNT_2_BIT;
        }
        else if (strcmp(str,"VK_SAMPLE_COUNT_4_BIT")==0)
        {
            data.samples = VK_SAMPLE_COUNT_4_BIT;
        }
        else if (strcmp(str,"VK_SAMPLE_COUNT_8_BIT")==0)
        {
            data.samples = VK_SAMPLE_COUNT_8_BIT;
        }
        else if (strcmp(str,"VK_SAMPLE_COUNT_16_BIT")==0)
        {
            data.samples = VK_SAMPLE_COUNT_16_BIT;
        }
        else if (strcmp(str,"VK_SAMPLE_COUNT_32_BIT")==0)
        {
            data.samples = VK_SAMPLE_COUNT_32_BIT;
        }
        else if (strcmp(str,"VK_SAMPLE_COUNT_64_BIT")==0)
        {
            data.samples = VK_SAMPLE_COUNT_64_BIT;
        }
        if (__DEBUG)slog("VkAttachmentDescription samples: %i",data.samples);
    }
    str = sj_object_get_value_as_string(config,"loadOp");
    if (str)
    {
        if (strcmp(str,"VK_ATTACHMENT_LOAD_OP_LOAD")==0)
        {
            data.loadOp = VK_ATTACHMENT_LOAD_OP_LOAD;
        }
        else if (strcmp(str,"VK_ATTACHMENT_LOAD_OP_CLEAR")==0)
        {
            data.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        }
        else if (strcmp(str,"VK_ATTACHMENT_LOAD_OP_DONT_CARE")==0)
        {
            data.loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        }
        if (__DEBUG)slog("loadOp: %s : %i",str,data.loadOp);
    }
    str = sj_object_get_value_as_string(config,"storeOp");
    if (str)
    {
        if (strcmp(str,"K_ATTACHMENT_STORE_OP_STORE")==0)
        {
            data.storeOp = VK_ATTACHMENT_LOAD_OP_LOAD;
        }
        else if (strcmp(str,"VK_ATTACHMENT_STORE_OP_DONT_CARE")==0)
        {
            data.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        }
        if (__DEBUG)slog("storeOp: %s : %i",str,data.storeOp);
    }
    str = sj_object_get_value_as_string(config,"stencilLoadOp");
    if (str)
    {
        if (strcmp(str,"VK_ATTACHMENT_LOAD_OP_LOAD")==0)
        {
            data.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_LOAD;
        }
        else if (strcmp(str,"VK_ATTACHMENT_LOAD_OP_CLEAR")==0)
        {
            data.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        }
        else if (strcmp(str,"VK_ATTACHMENT_LOAD_OP_DONT_CARE")==0)
        {
            data.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        }
        if (__DEBUG)slog("stencilLoadOp: %s : %i",str,data.stencilLoadOp);
    }
    str = sj_object_get_value_as_string(config,"stencilStoreOp");
    if (str)
    {
        if (strcmp(str,"K_ATTACHMENT_STORE_OP_STORE")==0)
        {
            data.stencilStoreOp = VK_ATTACHMENT_LOAD_OP_LOAD;
        }
        else if (strcmp(str,"VK_ATTACHMENT_STORE_OP_DONT_CARE")==0)
        {
            data.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        }
        if (__DEBUG)slog("stencilStoreOp: %s : %i",str,data.stencilStoreOp);
    }
    str = sj_object_get_value_as_string(config,"initialLayout");
    if (str)
    {
        data.initialLayout = gf3d_config_image_layer_from_str(str);
        if (__DEBUG)slog("initialLayout: %s : %i",str,data.initialLayout);
    }
    str = sj_object_get_value_as_string(config,"finalLayout");
    if (str)
    {
        data.finalLayout = gf3d_config_image_layer_from_str(str);
        if (__DEBUG)slog("finalLayout: %s : %i",str,data.finalLayout);
    }
    return data;
}

/*eol@eof*/
