#ifndef GENERATOR_GLADE_HPP_
#define GENERATOR_GLADE_HPP_

#include <string>

const std::string generator_glade = R"glade(
<?xml version="1.0" encoding="UTF-8"?>
<!-- Generated with glade 3.18.3 -->
<interface>
  <requires lib="gtk+" version="3.12"/>
  <object class="GtkWindow" id="main_window">
    <property name="can_focus">False</property>
    <child>
      <object class="GtkBox" id="main_box">
        <property name="visible">True</property>
        <property name="can_focus">False</property>
        <property name="orientation">vertical</property>
        <property name="spacing">5</property>
        <property name="homogeneous">True</property>
        <child>
          <object class="GtkLabel" id="title_label">
            <property name="visible">True</property>
            <property name="can_focus">False</property>
            <property name="label" translatable="yes">PI GENERATOR</property>
            <property name="justify">center</property>
            <property name="ellipsize">middle</property>
          </object>
          <packing>
            <property name="expand">False</property>
            <property name="fill">True</property>
            <property name="position">0</property>
          </packing>
        </child>
        <child>
          <object class="GtkGrid" id="result_grid">
            <property name="visible">True</property>
            <property name="can_focus">False</property>
            <property name="row_homogeneous">True</property>
            <property name="column_homogeneous">True</property>
            <child>
              <object class="GtkLabel" id="label_A1">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
                <property name="label" translatable="yes">PI</property>
              </object>
              <packing>
                <property name="left_attach">0</property>
                <property name="top_attach">0</property>
              </packing>
            </child>
            <child>
              <object class="GtkLabel" id="label_B1">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
              </object>
              <packing>
                <property name="left_attach">1</property>
                <property name="top_attach">0</property>
              </packing>
            </child>
            <child>
              <object class="GtkLabel" id="label_A2">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
                <property name="label" translatable="yes">result error</property>
              </object>
              <packing>
                <property name="left_attach">0</property>
                <property name="top_attach">1</property>
              </packing>
            </child>
            <child>
              <object class="GtkLabel" id="label_B2">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
              </object>
              <packing>
                <property name="left_attach">1</property>
                <property name="top_attach">1</property>
              </packing>
            </child>
          </object>
          <packing>
            <property name="expand">False</property>
            <property name="fill">True</property>
            <property name="position">1</property>
          </packing>
        </child>
        <child>
          <object class="GtkProgressBar" id="progress_bar">
            <property name="visible">True</property>
            <property name="can_focus">False</property>
            <property name="margin_top">10</property>
            <property name="margin_bottom">10</property>
            <property name="show_text">True</property>
          </object>
          <packing>
            <property name="expand">False</property>
            <property name="fill">True</property>
            <property name="position">2</property>
          </packing>
        </child>
        <child>
          <object class="GtkBox" id="button_box">
            <property name="visible">True</property>
            <property name="can_focus">False</property>
            <property name="homogeneous">True</property>
            <child>
              <object class="GtkButton" id="continue_button">
                <property name="label" translatable="yes">GENERATE!</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
              </object>
              <packing>
                <property name="expand">False</property>
                <property name="fill">True</property>
                <property name="position">0</property>
              </packing>
            </child>
            <child>
              <object class="GtkButton" id="exit_button">
                <property name="label" translatable="yes">CLOSE</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
              </object>
              <packing>
                <property name="expand">False</property>
                <property name="fill">True</property>
                <property name="position">1</property>
              </packing>
            </child>
          </object>
          <packing>
            <property name="expand">False</property>
            <property name="fill">True</property>
            <property name="position">3</property>
          </packing>
        </child>
      </object>
    </child>
  </object>
</interface>
)glade";

#endif
