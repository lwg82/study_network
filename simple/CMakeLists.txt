project(simple)

set(HEAD_FILES
  person.hpp
)

set(SRC_FILES
  hello.c
  person.cpp
)


add_executable(${PROJECT_NAME}
  ${HEAD_FILES}
  ${SRC_FILES}
)