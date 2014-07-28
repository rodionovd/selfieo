//
//  selfieo.c
//  selfieo
//
//  Created by Dmitry Rodionov on 7/28/14.
//  Copyright (c) 2014 rodionovd. All rights reserved.
//

#include <stdio.h>
#include <dlfcn.h>
#include <mach-o/dyld.h>
#include <mach-o/loader.h>
#include <mach/kern_return.h>
#include "selfieo.h"

/* I mean, you can also check argv for the output path, but it's just a PoC */
#define kDumpFilepath "/Users/rodionovd/Desktop/process_dump.bin"

/* This function will be executed when the library gets loaded into the target process */
__attribute__((constructor))
void init(int argc, const char *argv[])
{
    int err = selfieo(kDumpFilepath);
    if (err != KERN_SUCCESS) {
        fprintf(stderr, "selfieo() failed!");
    } else {
        fprintf(stderr, "Dumped to [%s]", kDumpFilepath);
    }
}


int selfieo(const char *output_file)
{
    /* A process main mach-o image has index 0 */
    struct mach_header_64 *header = (struct mach_header_64 *)_dyld_get_image_header(0);
    struct load_command *last_lc = (struct load_command *)(header + 1);

    uint64_t fileoffset_of_last_segment = 0;
    uint64_t filesize_of_last_segment = 0;
    /* Iterate all load commands (LC) to find out a file `offset` and a `size` of the last one,
     * so the whole file size will be equal to [`offset` + `size`] */
    for (uint32_t i = 0; i < header->ncmds; i++ ) {
        if (last_lc->cmd == LC_SEGMENT_64) {
            struct segment_command_64 *seg = (struct segment_command_64 *)last_lc;
            if (fileoffset_of_last_segment < seg->fileoff)
            {
                fileoffset_of_last_segment = seg->fileoff;
                filesize_of_last_segment   = seg->filesize;
            }
        }
        last_lc = (void *)last_lc + last_lc->cmdsize;
    }

    uint64_t image_size = fileoffset_of_last_segment + filesize_of_last_segment;

    /* Dump the whole binary to a file */
    FILE *output = fopen(output_file, "w");
    if (!output) {
        fprintf(stderr, "%s: could not open file [%s] for writing\n", __FUNCTION__, output_file);
        return KERN_FAILURE;
    }
    size_t result = fwrite(header, 1, image_size, output);
    fclose(output);

    return (image_size == result) ? KERN_SUCCESS : KERN_FAILURE;
}
