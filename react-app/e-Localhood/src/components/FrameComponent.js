import FrameComponent1 from "./FrameComponent1";
import "./FrameComponent.css";

const FrameComponent = () => {
  return (
    <div className="city-rectangle1">
      <div className="state-text">
        <div className="your-store-name6">Your Store Name</div>
        <input className="pincode-text" type="text" />
      </div>
      <FrameComponent1 pincode="Pincode*" />
      <div className="state-text1">
        <div className="city">City*</div>
        <input className="state-text-child" type="text" />
      </div>
      <div className="location-details-frame">
        <div className="state">State*</div>
        <div className="frame-with-ellipses">
          <div className="frame-with-ellipses-child" />
          <input
            className="maharashtra"
            placeholder="Maharashtra"
            type="text"
          />
          <img className="bank-details-frame1" alt="" src="/vector-3.svg" />
        </div>
      </div>
      <div className="area-street-shop">Area, street, Shop no.*</div>
      <input className="frame-with-text-area-and-recta" type="text" />
    </div>
  );
};

export default FrameComponent;
