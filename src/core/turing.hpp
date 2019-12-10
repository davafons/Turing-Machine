#pragma once

#include "data/alphabet.hpp"
#include "state/state.hpp"
#include "utils/utils.hpp"

namespace turing {

class Turing {
public:
  Turing(int num_tapes = 1, int num_tracks = 1);
  ~Turing();

  Alphabet& tapeAlphabet();
  const Alphabet& tapeAlphabet() const;

  Alphabet& inputAlphabet();
  const Alphabet& inputAlphabet() const;

  // States
  State* state(const std::string& name);
  bool hasState(const std::string& name);

  const State* startState() const;
  void setInitialState(const std::string& name);

  void setFinalStates(const std::vector<std::string>& state_names);

  void addState(const std::string& s);
  void addStates(const std::vector<std::string>& names_str);

  // Transitions
  void addTransition(const std::string& start_state_name,
                     const Cell& input_symbols,
                     const std::string& end_state_name,
                     const Cell& output_symbols,
                     const Move& movement);

  // Turing Machine
  bool debugMode() const;
  void toggleDebugMode(bool toggle);

  bool run(const std::string& input_string);

private:
  Alphabet input_alphabet_;
  Alphabet tape_alphabet_;

  State* start_state_{nullptr};

  std::vector<Tape> tapes_;
  int tape_tracks_{1};

  std::map<std::string, State*> states_;

  bool debug_mode_{false};
};

}  // namespace turing
