/**
 * @file scp_graph_line.h
 *
 * @brief Componenets for drawing graph lines.
 *
 * @ingroup SimpleCustomPlotInternal
 *
 * @author Frans Rosencrantz
 * Contact: Frans.Rosencrantz@gmail.com
 *
 */

#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include "scp_datamodels.h"
#include "scp_internal_datamodels.h"

namespace scp {
//==============================================================================
/**
 *  \class GraphLine
 *  \brief A templated class component to draw 2-D lines/marker symbols. This is
 *  a subcomponenet to scp::Plot.
 *
 *  Never use this directley, always use one of the derived classes to choose
 *  the scaling.
 */
class GraphLine : public juce::Component {
 public:
  std::pair<juce::Point<float>, juce::Point<float>> findClosestGraphPointTo(
      const juce::Point<float>& point) const noexcept;

  /** @brief Get the colour of graph
   *
   *  Get the colour of graph.
   *
   *  @param graph_colour the colour of the graph
   *  @return void.
   */
  juce::Colour getColour() const noexcept;

  /** @brief Set the y-values for the graph-line
   *
   *  Set the y-values.
   *
   *  @param y_values vector of y-values.
   *  @return void.
   */
  void setYValues(const std::vector<float>& y_values) noexcept;

  /** @brief Set the x-values for the graph-line
   *
   *  Set the x-values.
   *
   *  @param x_values vector of x-values.
   *  @return void.
   */
  void setXValues(const std::vector<float>& x_values) noexcept;

  /** @brief Get y-values
   *
   *  Get a const reference of the y-values.
   *
   *  @return a const reference of the y-values.
   */
  const std::vector<float>& getYValues() noexcept;

  /** @brief Get x-values
   *
   *  Get a const reference of the x-values.
   *
   *  @return a const reference of the x-values.
   */
  const std::vector<float>& getXValues() noexcept;

  /** @brief Get the graph points
   *
   *  Get a const reference of the calculated graph points.
   *
   *  @return const reference of the calculated graph points.
   */
  const GraphPoints& getGraphPoints() noexcept;

  /** @brief Set the colour of graph
   *
   *  Set the colour of graph.
   *
   *  @param graph_colour the colour of the graph
   *  @return void.
   */
  void setColour(const juce::Colour graph_colour);

  /** @brief Set a dashed path
   *
   *  Use custom dash-lengths to draw a dashed line. e.g. dashed_lengths = {2,
   *  2, 4, 6} will draw a line of 2 pixels, skip 2 pixels, draw 3 pixels, skip
   *  6 pixels, and then repeat.
   *
   *  @param dashed_lengths
   *  @return void.
   */
  void setDashedPath(const std::vector<float>& dashed_lengths) noexcept;

  /** @brief Update the x-value in the graph points.
   *
   *  This function updates the graph points if any new parameter is set. Should
   *  be called after an parameter changed to update the graph.
   *
   *  @param graph_attributes common graph attributes.
   *  @return void.
   */
  void updateXGraphPoints(const GraphAttributesView& graph_attribute);

  /** @brief Update the y-value in the graph points.
   *
   *  This function updates the graph points if any new parameter is set. Should
   *  be called after an parameter changed to update the graph.
   *
   *  @param graph_attributes common graph attributes.
   *  @return void.
   */
  void updateYGraphPoints(const GraphAttributesView& graph_attribute);

  //==============================================================================
  /** @internal */
  void resized() override;
  /** @internal */
  void paint(juce::Graphics& g) override;
  /** @internal */
  void lookAndFeelChanged() override;

 private:
  /** @brief An enum to describe the state of the graph.  */
  enum class State {
    Uninitialized,
    Initialized,
  } m_state{State::Uninitialized};

  std::vector<float> m_dashed_lengths;
  juce::Colour m_graph_colour;

  void updateYGraphPointsIntern(const GraphAttributesView& graph_attribute) noexcept;
  void updateXGraphPointsIntern(const GraphAttributesView& graph_attribute) noexcept;

 protected:
  juce::LookAndFeel* m_lookandfeel{nullptr};

  std::vector<float> m_x_data, m_y_data;
  GraphPoints m_graph_points;
  std::vector<std::size_t> m_graph_point_indices;
};
}  // namespace scp
