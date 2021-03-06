#ifndef CONVERTER_GLADE_HPP_
#define CONVERTER_GLADE_HPP_

#include <string>

const std::string converter_glade = R"Glade(
<?xml version="1.0" encoding="UTF-8"?>
<!-- Generated with glade 3.22.2 -->
<interface>
  <requires lib="gtk+" version="3.12"/>
  <object class="GtkAdjustment" id="base_result_adjustment">
    <property name="lower">2</property>
    <property name="upper">16</property>
    <property name="value">10</property>
    <property name="step_increment">1</property>
    <property name="page_increment">1</property>
  </object>
  <object class="GtkAdjustment" id="base_value_adjustment">
    <property name="lower">2</property>
    <property name="upper">16</property>
    <property name="value">10</property>
    <property name="step_increment">1</property>
    <property name="page_increment">1</property>
  </object>
  <object class="GtkWindow" id="main_window">
    <property name="can_focus">False</property>
    <child type="titlebar">
      <placeholder/>
    </child>
    <child>
      <object class="GtkBox" id="main_box">
        <property name="visible">True</property>
        <property name="can_focus">False</property>
        <property name="orientation">vertical</property>
        <property name="homogeneous">True</property>
        <child>
          <object class="GtkLabel" id="title_label">
            <property name="visible">True</property>
            <property name="can_focus">False</property>
            <property name="label" translatable="yes">CONVERTER</property>
            <property name="justify">fill</property>
            <property name="ellipsize">middle</property>
          </object>
          <packing>
            <property name="expand">False</property>
            <property name="fill">True</property>
            <property name="position">0</property>
          </packing>
        </child>
        <child>
          <object class="GtkGrid" id="data_grid">
            <property name="visible">True</property>
            <property name="can_focus">False</property>
            <property name="row_homogeneous">True</property>
            <property name="column_homogeneous">True</property>
            <child>
              <object class="GtkLabel" id="value_label">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
                <property name="label" translatable="yes">VALUE</property>
              </object>
              <packing>
                <property name="left_attach">0</property>
                <property name="top_attach">0</property>
              </packing>
            </child>
            <child>
              <object class="GtkLabel" id="base_value_label">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
                <property name="label" translatable="yes">BASE OF VALUE</property>
              </object>
              <packing>
                <property name="left_attach">0</property>
                <property name="top_attach">1</property>
              </packing>
            </child>
            <child>
              <object class="GtkLabel" id="base_result_label">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
                <property name="label" translatable="yes">BASE OF RESULT</property>
              </object>
              <packing>
                <property name="left_attach">0</property>
                <property name="top_attach">2</property>
              </packing>
            </child>
            <child>
              <object class="GtkEntry" id="value_entry">
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="caps_lock_warning">False</property>
                <property name="input_purpose">alpha</property>
              </object>
              <packing>
                <property name="left_attach">1</property>
                <property name="top_attach">0</property>
              </packing>
            </child>
            <child>
              <object class="GtkSpinButton" id="base_value_spinbutton">
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="caps_lock_warning">False</property>
                <property name="input_purpose">number</property>
                <property name="adjustment">base_value_adjustment</property>
                <property name="climb_rate">1</property>
                <property name="numeric">True</property>
                <property name="value">10</property>
              </object>
              <packing>
                <property name="left_attach">1</property>
                <property name="top_attach">1</property>
              </packing>
            </child>
            <child>
              <object class="GtkSpinButton" id="base_result_spinbutton">
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="caps_lock_warning">False</property>
                <property name="input_purpose">number</property>
                <property name="adjustment">base_result_adjustment</property>
                <property name="climb_rate">1</property>
                <property name="numeric">True</property>
                <property name="value">10</property>
              </object>
              <packing>
                <property name="left_attach">1</property>
                <property name="top_attach">2</property>
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
          <object class="GtkLabel" id="result_label">
            <property name="visible">True</property>
            <property name="can_focus">False</property>
            <property name="justify">center</property>
            <property name="ellipsize">middle</property>
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
              <object class="GtkButton" id="convert_button">
                <property name="label" translatable="yes">CONVERT!</property>
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
              <object class="GtkButton" id="close_button">
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
)Glade";

#endif
