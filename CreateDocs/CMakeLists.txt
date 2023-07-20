# This errors out if doxygen is not found
find_package(Doxygen REQUIRED)

set(CREATEDOCS_SOURCE_DIR ${CMAKE_SOURCE_DIR}/CreateDocs)
set(CREATEDOCS_OUTPUT_DIR ${CMAKE_BINARY_DIR}/CreateDocs)
set(EXTERNAL_DOCS_DIR ${CREATEDOCS_SOURCE_DIR}/../docs)

add_custom_target(CreateDocs ALL
    DEPENDS doxy_files
)

# Use the Doxygen::doxygen imported target as the command.
#
# The old way of invoking Doxygen looked like this:
#COMMAND ${CMAKE_COMMAND} -E env
#    ${DOXYGEN_EXECUTABLE} Doxyfile >${CREATEDOCS_OUTPUT_DIR}/doxy.out
add_custom_command(OUTPUT doxy_files
    COMMAND Doxygen::doxygen Doxyfile >${CREATEDOCS_OUTPUT_DIR}/doxy.out
    COMMENT "Creating documentation with doxygen..."
    WORKING_DIRECTORY ${CREATEDOCS_SOURCE_DIR}
)

set_source_files_properties(doxy_files PROPERTIES SYMBOLIC true)

target_sources(CreateDocs
    PRIVATE
        ${CREATEDOCS_SOURCE_DIR}/Doxyfile
        ${CREATEDOCS_SOURCE_DIR}/pageheader.html
        ${CREATEDOCS_SOURCE_DIR}/pagefooter.html
        ${CREATEDOCS_SOURCE_DIR}/pagestyle.css
        ${CREATEDOCS_SOURCE_DIR}/explain.css
    PRIVATE
        ${EXTERNAL_DOCS_DIR}/abstract_factory.md
        ${EXTERNAL_DOCS_DIR}/adapter.md
        ${EXTERNAL_DOCS_DIR}/bridge.md
        ${EXTERNAL_DOCS_DIR}/builder.md
        ${EXTERNAL_DOCS_DIR}/command.md
        ${EXTERNAL_DOCS_DIR}/composite.md
        ${EXTERNAL_DOCS_DIR}/decorator.md
        ${EXTERNAL_DOCS_DIR}/facade.md
        ${EXTERNAL_DOCS_DIR}/factory.md
        ${EXTERNAL_DOCS_DIR}/flyweight.md
        ${EXTERNAL_DOCS_DIR}/handlerchain.md
        ${EXTERNAL_DOCS_DIR}/interpreter.md
        ${EXTERNAL_DOCS_DIR}/iterator.md
        ${EXTERNAL_DOCS_DIR}/mainpage.md
        ${EXTERNAL_DOCS_DIR}/mediator.md
        ${EXTERNAL_DOCS_DIR}/memento.md
        ${EXTERNAL_DOCS_DIR}/nullobject.md
        ${EXTERNAL_DOCS_DIR}/observer.md
        ${EXTERNAL_DOCS_DIR}/private.md
        ${EXTERNAL_DOCS_DIR}/prototype.md
        ${EXTERNAL_DOCS_DIR}/proxy.md
        ${EXTERNAL_DOCS_DIR}/singleton.md
        ${EXTERNAL_DOCS_DIR}/state.md
        ${EXTERNAL_DOCS_DIR}/strategy.md
        ${EXTERNAL_DOCS_DIR}/template.md
        ${EXTERNAL_DOCS_DIR}/visitor.md
)

source_group("Document Files" REGULAR_EXPRESSION .*\.md)
source_group("Source Files" FILES Doxyfile pageheader.html. pagefooter.html pagestyle.css explain.css)
