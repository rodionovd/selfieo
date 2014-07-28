//
//  selfieo.h
//  selfieo
//
//  Created by Dmitry Rodionov on 7/28/14.
//  Copyright (c) 2014 rodionovd. All rights reserved.
//

#ifndef selfieo_h
    #define selfieo_h

/**
 * Dumps in-memory image of the current process to a file.
 *
 * @param output_file
 * Full path of the output file.
 *
 * @return
 * KERN_SUCCESS if the dumping ended up successfully
 * KERN_FAILURE if it didn't
 */
int selfieo(const char *output_file);

#endif
