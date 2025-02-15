/**
 * @file static_literals.h
 *
 * A set of static literal nodes that can be checked for duplicates.
 */
#ifndef PRISM_STATIC_LITERALS_H
#define PRISM_STATIC_LITERALS_H

#include "prism/defines.h"
#include "prism/ast.h"
#include "prism/node.h"
#include "prism/parser.h"

#include <assert.h>
#include <stdbool.h>

/**
 * Certain sets of nodes (hash keys and when clauses) check for duplicate nodes
 * to alert the user of potential issues. To do this, we keep a set of the nodes
 * that have been seen so far, and compare whenever we find a new node.
 *
 * We bucket the nodes based on their type to minimize the number of comparisons
 * that need to be performed.
 */
typedef struct {
    /**
     * This is the set of IntegerNode and SourceLineNode instances. We store
     * them in a sorted list so that we can binary search through them to find
     * duplicates.
     */
    pm_node_list_t integer_nodes;

    /**
     * This is the set of FloatNode instances. We store them in a sorted list so
     * that we can binary search through them to find duplicates.
     */
    pm_node_list_t float_nodes;

    /**
     * This is the set of RationalNode instances. We store them in a flat list
     * that must be searched linearly.
     */
    pm_node_list_t rational_nodes;

    /**
     * This is the set of ImaginaryNode instances. We store them in a flat list
     * that must be searched linearly.
     */
    pm_node_list_t imaginary_nodes;

    /**
     * This is the set of StringNode and SourceFileNode instances. We store them
     * in a sorted list so that we can binary search through them to find
     * duplicates.
     */
    pm_node_list_t string_nodes;

    /**
     * This is the set of RegularExpressionNode instances. We store them in a
     * sorted list so that we can binary search through them to find duplicates.
     */
    pm_node_list_t regexp_nodes;

    /**
     * This is the set of SymbolNode instances. We store them in a sorted list
     * so that we can binary search through them to find duplicates.
     */
    pm_node_list_t symbol_nodes;

    /**
     * A pointer to the last TrueNode instance that was inserted, or NULL.
     */
    pm_node_t *true_node;

    /**
     * A pointer to the last FalseNode instance that was inserted, or NULL.
     */
    pm_node_t *false_node;

    /**
     * A pointer to the last NilNode instance that was inserted, or NULL.
     */
    pm_node_t *nil_node;

    /**
     * A pointer to the last SourceEncodingNode instance that was inserted, or
     * NULL.
     */
    pm_node_t *source_encoding_node;
} pm_static_literals_t;

/**
 * Add a node to the set of static literals.
 *
 * @param parser The parser that created the node.
 * @param literals The set of static literals to add the node to.
 * @param node The node to add to the set.
 * @return A pointer to the node that is being overwritten, if there is one.
 */
pm_node_t * pm_static_literals_add(const pm_parser_t *parser, pm_static_literals_t *literals, pm_node_t *node);

/**
 * Free the internal memory associated with the given static literals set.
 *
 * @param literals The set of static literals to free.
 */
void pm_static_literals_free(pm_static_literals_t *literals);

#endif
