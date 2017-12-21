// Copyright (c) 2017 Sony Corporation. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include <nnablart/network.h>
#include <nnablart/runtime.h>

#include "dump.h"
#include "infer.h"

static void usage(const char *err) { printf("Error [%s]\n", err); }

int main(int argc, char *argv[]) {
  int ret = -1;

  if (argc < 3) {
    usage("No subcommand.");
  } else {
    char *subcmd = argv[1];
    char *nnb_filename = argv[2];
    argv += 3;
    argc -= 3;

    FILE *nnb = fopen(nnb_filename, "rb");
    assert(nnb);
    fseek(nnb, 0L, SEEK_END);
    size_t nnb_data_size = ftell(nnb);
    fseek(nnb, 0L, SEEK_SET);
    uint8_t *nnb_data = malloc(nnb_data_size);
    assert(nnb_data);
    int read_size = fread(nnb_data, sizeof(uint8_t), nnb_data_size, nnb);
    assert(read_size == nnb_data_size);
    fclose(nnb);
    nn_network_t *net = (nn_network_t *)nnb_data;

    if (strncmp("dump", subcmd, 4) == 0) {
      ret = dump(net, argc, argv);
    } else if (strncmp("infer", subcmd, 5) == 0) {
      ret = infer(net, argc, argv);
    } else {
      usage("Unknown subcommand");
    }

    free(nnb_data);
  }
  return ret;
}
