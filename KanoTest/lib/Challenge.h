#pragma once 

#include <string>
#include <regex>
#include <vector>

#include "json.hpp"
using json = nlohmann::json;

class Challenge {
public:

	class Step {
	public:
		Step(std::string instruction, std::regex validate) {
			m_strInstruction = instruction;
			m_rgxValidate = validate;
		}

		Step(std::string instruction, std::string validate) {
			m_strInstruction = instruction;
			m_rgxValidate = validate;
		}

        bool Validate(std::string input) {
			return std::regex_match(input, m_rgxValidate);
		}

        std::string GetInstruction() {
            return m_strInstruction;
        }

	private:
		std::string m_strInstruction;
		std::regex m_rgxValidate;
	};

public:
	Challenge(const char* input) {
        ParseJSON(json::parse(input));
	}

	Challenge(std::string input) {
        ParseJSON(json::parse(input.c_str()));
	}

	Challenge(json input) {
        ParseJSON(input);
	}

	std::vector<Step>::iterator begin() {
		return m_vecSteps.begin();
	}

	std::vector<Step>::iterator end() {
		return m_vecSteps.end();
	}

	std::vector<Step>::const_iterator cbegin() {
		return m_vecSteps.begin();
	}

	std::vector<Step>::const_iterator cend() {
		return m_vecSteps.end();
	}

	std::string GetTitle() {
		return m_strTitle;
	}

	Step& operator[](std::size_t idx) {
		return m_vecSteps[idx];
	}

	bool IsValid() { return is_valid;  }

	std::string GetErrorString() { return error_string; }

private:
    void ParseJSON(json input) {
		try
		{
			for (auto& base_element : input) {
				for (auto& upper_element : base_element) {
					if (upper_element.type() == json::value_t::string) {
						m_strTitle = upper_element.get<std::string>();
					}
					else if (upper_element.type() == json::value_t::object) {
						auto instruction = upper_element["instruction"].get<std::string>();
						auto validate = upper_element["validate"].get<std::string>();
						m_vecSteps.push_back(Step(instruction, validate));
					}
				}
			}

			is_valid = true;
		}
		catch (const std::exception& e)
		{
			error_string = e.what();
		}	
	}

private:
	std::string m_strTitle;
	std::vector<Step> m_vecSteps;
	bool is_valid = false;
	std::string error_string;
};
