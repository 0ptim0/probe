# Probe

Tiny C Unit Testing Framework for use in Embedded Systems

## Table of Contents

- [Project Name](#project-name)
  - [Table of Contents](#table-of-contents)
  - [Description](#description)
  - [Features](#features)
  - [Installation](#installation)
  - [Usage](#usage)
  - [Documentation](#documentation)
  - [Contributing](#contributing)
  - [License](#license)
  - [Contact](#contact)

## Description

Macro-based framework for unit testing on hosts and targets

## Features

- Only two files
- Easy to integrate into any C/C++ project
- Uses only one external function that can be overridden
- Convenient to use in embedded systems

## Installation
### 1. Downloading
As a part of your sources
```shell
cd /path/to/test/dir
curl -L https://github.com/0ptim0/probe/archive/refs/tags/v1.0.0.zip | tar xz
```

As a submodule
```shell
cd /path/to/test/dir
git submodule add https://github.com/0ptim0/probe
```

### 2. Add sources to a build system
#### make
```make
SRC += /path/to/probe/dir/probe.c
INC += /path/to/probe/dir
```

#### cmake
```cmake
add_executable(tests
    probe/probe.c
    [path/to/test_source_1.c]
    [path/to/test_source_2.c]
    ...
)

target_include_directories(tests PUBLIC
    probe
    [path/to/header_1]
    [path/to/header_2]
    ...
)
```

## Usage
```c
// Here's a example that tests a queue API
#include "../include/queue.h"

#include "probe.h"

TEST(QueueInit) {
    queue_init(q1, 1024, 32);
    CHECK_NOT_NULL(&q1);
}

TEST(QueuePushPop) {
    queue_init(q1, 1024, 32);
    CHECK_NOT_NULL(&q1);
    char wdata[32] = "0xDEADBEEF";
    CHECK_ZERO(queue_push(&q1, wdata));
    char rdata[32] =  {0};
    CHECK_ZERO(queue_pop(&q1, rdata));
    CHECK_STR(wdata, rdata);
}
```

