#include "StateMachineParser.h"

#include "easy_prop.h"
#include "FlexibleFA.h"
#include "set_operations.h"

#include "ParseFFLOATDot.h"
StateMachineParser* StateMachineParser::uniqueInstance = nullptr;

inline
std::unordered_set<std::string> evaluate_easy_prop_to_atoms(const easy_prop& prop,
    const std::unordered_set<std::string>& sigma) {
    switch (prop.casusu) {
    case easy_prop::E_P_AND:
        //            DEBUG_ASSERT(prop.args.size() == 2);
        //            DEBUG_ASSERT(!prop.isAtomNegated);
        return unordered_intersection(evaluate_easy_prop_to_atoms(prop.args.at(0)/*, bogus_act_to_atom*/, sigma),
            evaluate_easy_prop_to_atoms(prop.args.at(1)/*, bogus_act_to_atom*/, sigma));
    case easy_prop::E_P_OR: {
        //            DEBUG_ASSERT(prop.args.size() == 2);
        //            DEBUG_ASSERT(!prop.isAtomNegated);
        auto S = evaluate_easy_prop_to_atoms(prop.args.at(0)/*, bogus_act_to_atom*/, sigma);
        auto tmp = evaluate_easy_prop_to_atoms(prop.args.at(1)/*, bogus_act_to_atom*/, sigma);
        S.insert(tmp.begin(), tmp.end());
        return S;
    }
    case easy_prop::E_P_ATOM:
        //            DEBUG_ASSERT(prop.args.empty());
        //            DEBUG_ASSERT(bogus_act_to_set.contains(prop.single_atom_if_any));
        if (prop.isAtomNegated) {
            auto it = sigma.find(prop.single_atom_if_any);
            if (it != sigma.end()) {
                return unordered_difference(sigma, { prop.single_atom_if_any });
            }
            else {
                return sigma;
            }
        }
        else {
            return { prop.single_atom_if_any };
        }
    case easy_prop::E_P_TRUE:
        return sigma;
    default: //case easy_prop::E_P_FALSE:
        return {};
    }
}
NCL::CSC8599::StateMachine* StateMachineParser::parse(ltlf& formula)
{
    // Set of all of the possible labels of the graph
    std::unordered_set<std::string> sigmaAll{ "f", "g", "h" };

    std::stringstream s;
    // Representing the formula as per online syntax
    s << formula;

    // Graph in the dotviz representation
    std::string dot_graph = callable(s.str());
    // Representing the string as a stream
    std::stringstream file{ dot_graph };

    // Parsing the file by reading the graphviz representation for it
    ParseFFLOATDot graph_loader;
    auto patternGraphToInstantiate = graph_loader.parse(file);

    // Converting the graph with propositions into a DFA
    FlexibleFA<size_t, std::string> result;
    std::unordered_map<size_t, size_t> idConv;
    for (size_t nodeId = 0, N = patternGraphToInstantiate.maximumNodeId(); nodeId < N; nodeId++) {
        size_t src = result.addNewNodeWithLabel(nodeId);
        idConv[nodeId] = src;
    }
    for (size_t finalNodes : patternGraphToInstantiate.fini()) {
        result.addToFinalNodesFromId(idConv.at(finalNodes));
    }
    for (size_t initialNodes : patternGraphToInstantiate.init()) {
        result.addToInitialNodesFromId(idConv.at(initialNodes));
    }
    for (size_t nodeId = 0, N = patternGraphToInstantiate.maximumNodeId(); nodeId < N; nodeId++) {
        size_t src = idConv.at(nodeId);
        for (const auto& edge : patternGraphToInstantiate.outgoingEdges(nodeId)) {
            // std::cerr << edge.first << std::endl;
            size_t dst = idConv.at(edge.second);
            for (const std::string& act : evaluate_easy_prop_to_atoms(edge.first/*, bogus_act_to_atom*/, sigmaAll)) {
                result.addNewEdgeFromId(src, dst, act);
            }
        }
    }
    result.makeDFAAsInTheory(sigmaAll);

    // Printing the result into the terminal in a graphviz syntax
    result.dot(std::cout);
    std::cout << std::endl;
    return 0;
}

StateMachineParser* StateMachineParser::getInstance()
{

    if (uniqueInstance == nullptr) {
        uniqueInstance = new StateMachineParser();
    }
    return uniqueInstance;
}

StateMachineParser::StateMachineParser()
{

}
