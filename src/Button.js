import React from 'react';
import styles from './Button.css';

export default class Button extends React.Component {
  render() {
    return (
      <button onClick={() => this.props.handleButtonClick()}>{`${
        this.props.label
      }`}</button>
    );
  }
}
